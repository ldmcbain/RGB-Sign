/*
 * ENDEAVOR LED SIGN CONTROL
 * This project was created by Endeavor Labs (a mission of Endeavor Church) to create
 * an LED controller for the main front sign.  
 * 
 * The system is to be designed to use a ESP32 Dev board to control 3 separate
 * RGBW 5050 LED strips.  The LEDs will be driven via NMOS FETs on the attached 
 * PCB.
 * 
 * This software is designed to create a permanent Access Point with a captive portal
 * to a webpage which will control the three strings using the jscolor color picker 
 * (jscolor.js stored in SPIFFS). The device will then present the user with the
 * ability to save the settings to EEPROM so that the unit will restore settings
 * upon reboot (which will occurr nightly).
 * 
 * This is version 2 which added the white LEDs and also is being used with
 * the incorporated PCB attached to the project.
 * 
 * Board - ESP32 Dev Module
 * Upload Speed - 115200
 * CPU Freq - 240MHz
 * Flash Freq 40MHz
 * Mode - QIO
 * Flash size - 4MB (32Mb)
 * Partition - Default 4MB wigh SPIFFS (1.2MB APP/1.5MB SPIFFS)
 */

#include <Arduino.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "./server_html.h"
#include "./myeeprom.h"
#include <SPIFFS.h>

#define FILESYSTEM SPIFFS

// Replace with your network credentials
const char* ssid     = "XXXXXXXX";
const char* password = "XXXXXXXX";

// Set web server port number to 80
WebServer server(80);
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;

// Red, green, and blue pins for PWM control
const int redPin[MAX_leds] = {13,27,4};     // 13 corresponds to GPIO13
const int greenPin[MAX_leds] = {12,26,2};   // 12 corresponds to GPIO12
const int bluePin[MAX_leds] = {14,25,15};    // 14 corresponds to GPIO14
const int whitePin[MAX_leds] = {17,32,16};    // 14 corresponds to GPIO14

// Setting PWM frequency, channels and bit resolution
//resolution set down to 300 to improve resolution in low/high settings.
const int freq = 300;
const int redChannel[MAX_leds] = {0,1,2};
const int greenChannel[MAX_leds] = {3,4,5};
const int blueChannel[MAX_leds] = {6,7,8};
const int whiteChannel[MAX_leds] = {9,10,11};
// Bit resolution 2^8 = 256
const int resolution = 8;

int redInt[3] = {0,0,0};
int blueInt[3] = {0,0,0};
int greenInt[3] = {0,0,0};
int whiteInt[3] = {0,0,0};

void handleRoot()
{
  buildWebsite();
  server.send(200, "text/html", webSite);
}

void handleLED1()
{
  handleLED(0,server.arg("r"),server.arg("g"),server.arg("b"));
}

void handleLED2()
{
  handleLED(1,server.arg("r"),server.arg("g"),server.arg("b"));
}

void handleLED3()
{
  handleLED(2,server.arg("r"),server.arg("g"),server.arg("b"));
}

void handleWHITE1()
{
  handleWHITE(0,server.arg("w"));
}

void handleWHITE2()
{
  handleWHITE(1,server.arg("w"));
}

void handleWHITE3()
{
  handleWHITE(2,server.arg("w"));
}

void handleSAVE()
{
  Serial.println("Saving Settings");
  int i;
  for(i=0;i<MAX_leds;i++)
  {
    Serial.printf("R%i:%s G%i:%s B%i:%s W%i:%s ",i,redString[i].c_str(),i,greenString[i].c_str(),i,blueString[i].c_str(),i,whiteString[i].c_str());
  }
  Serial.println("");
  saveSettings(redString[0],greenString[0],blueString[0],whiteString[0],
               redString[1],greenString[1],blueString[1],whiteString[1],
               redString[2],greenString[2],blueString[2],whiteString[2]);
}

void handleRESTORE()
{
  getStoredSettings();
  redString[0]=String(romSettings.RD1);
  greenString[0]=String(romSettings.GR1);
  blueString[0]=String(romSettings.BL1);
  whiteString[0]=String(romSettings.WH1);
  redString[1]=String(romSettings.RD2);
  greenString[1]=String(romSettings.GR2);
  blueString[1]=String(romSettings.BL2);
  whiteString[1]=String(romSettings.WH2);
  redString[2]=String(romSettings.RD3);
  greenString[2]=String(romSettings.GR3);
  blueString[2]=String(romSettings.BL3);
  whiteString[2]=String(romSettings.WH3);

  
  Serial.println("Restore String Settings");
  int i;
  for(i=0;i<MAX_leds;i++)
  {
    Serial.printf("R%i:%s G%i:%s B%i:%s W%i:%s ",i,redString[i].c_str(),i,greenString[i].c_str(),i,blueString[i].c_str(),i,whiteString[i].c_str());
  }
  Serial.println("");
  
  for(i=0;i<MAX_leds;i++)
  {
    handleLED(i,redString[i],greenString[i],blueString[i]);
    handleWHITE(i,whiteString[i]);
  }
}

void handleLED(int LED, String r, String g, String b)
{  
  redString[LED] = r;
  greenString[LED] = g;
  blueString[LED] = b;
  
  ledcWrite(redChannel[LED], r.toInt());
  ledcWrite(greenChannel[LED], g.toInt());
  ledcWrite(blueChannel[LED], b.toInt());
  
  Serial.print("LED");
  Serial.print(LED);
  Serial.print(" Set to: RED:");
  Serial.print(r);
  Serial.print(" GREEN:");
  Serial.print(g);
  Serial.print(" BLUE:");
  Serial.println(b);
}

void handleWHITE(int LED, String w)
{
  whiteString[LED] = w;
  ledcWrite(whiteChannel[LED], w.toInt());
  
  Serial.print("LED");
  Serial.print(LED);
  Serial.print(" Set to: WHITE:");
  Serial.println(w);
}

void setup() {
  Serial.begin(115200);
  int i;
  for(i=0;i<MAX_leds;i++)
  {
    // configure LED PWM functionalitites
    ledcSetup(redChannel[i], freq, resolution);
    ledcSetup(greenChannel[i], freq, resolution);
    ledcSetup(blueChannel[i], freq, resolution);
    ledcSetup(whiteChannel[i], freq, resolution);
    
    // attach the channel to the GPIO to be controlled
    ledcAttachPin(redPin[i], redChannel[i]);
    ledcAttachPin(greenPin[i], greenChannel[i]);
    ledcAttachPin(bluePin[i], blueChannel[i]);
    ledcAttachPin(whitePin[i], whiteChannel[i]);
  }

  // Initialize SPIFFS
  if(!FILESYSTEM.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  //restore settings from EEPROM
  handleRESTORE();
  
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Starting AP ");
  Serial.println(ssid);

  WiFi.mode(WIFI_AP);
  Serial.println(WiFi.softAP(ssid, password) ? "soft-AP setup": "Failed to connect");
  delay(100);
  Serial.println(WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0))? "Configuring Soft AP" : "Error in Configuration");


  //setup captive portal so all traffic goes to main page
  dnsServer.start(DNS_PORT, "*", apIP);
  
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP:");
  Serial.println(WiFi.softAPIP());
  startWebServer();
}

void loop(){
  dnsServer.processNextRequest();
  server.handleClient();
}

void startWebServer()
{  
  server.on("/jscolor.js", HTTP_GET, [](){
    if (!handleFileRead("/jscolor.js")) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });
  server.on( "/", handleRoot);
  server.on("/setLED1",handleLED1);
  server.on("/setLED2",handleLED2);
  server.on("/setLED3",handleLED3);
  server.on("/setWHITE1",handleWHITE1);
  server.on("/setWHITE2",handleWHITE2);
  server.on("/setWHITE3",handleWHITE3);
  server.on("/SAVE",handleSAVE);
  server.on("/RESTORE",handleRESTORE);
  server.onNotFound(handleRoot);
  server.begin();
}

bool handleFileRead(String path) {
  String contentType = getContentType(path);
  if (exists(path)) {
    File file = FILESYSTEM.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

String getContentType(String filename) {
  if (server.hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

bool exists(String path){
  bool yes = false;
  File file = FILESYSTEM.open(path, "r");
  if(!file.isDirectory()){
    yes = true;
  }
  file.close();
  return yes;
}
