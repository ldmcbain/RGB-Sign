
const int MAX_leds = 3;
String redString[MAX_leds] = {"00","00","00"};
String greenString[MAX_leds] = {"00","00","00"};
String blueString[MAX_leds] = {"00","00","00"};
String whiteString[MAX_leds] = {"00","00","00"};
String webSite;

void buildWebsite()
{

  webSite = "<!DOCTYPE HTML>\n";
  webSite += "<META name='viewport' content='width=device-width, initial-scale=1'>\n";
  webSite += "<script src=\"jscolor.js\"></script>";
  webSite += "<style type=""text/css"" media=""screen"">\n";
  webSite += "    .slider { -webkit-appearance: none; margin: 14px; width: 200px; height: 15px; border-radius: 5px; background: #39a6de; outline: none; -webkit-transition: .2s; transition: opacity .2s;}\n";
  webSite += "    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 25px; height: 25px; border-radius: 12px; background: #f74d4d; cursor: pointer;}\n";
  webSite += "    .slider::-moz-range-thumb { width: 25px; height: 25px; border-radius: 12px; background: #F74D4D; cursor: pointer; }\n";
  webSite += "</style>\n";
  //webSite += "<BODY onload='process()'>\n";
  webSite += "<BODY onload=\"init()\">\n";
  
  webSite += "<b>ENDEAVOR SIGN CONTROL</b><br>\n";
  webSite += "<b>LOGO:</b><br>";
  webSite += "<p>RGB LEDS<BR>";
  webSite += "<input id=\"picker1\" class=\"jscolor {closable:true,closeText:'Close me!',onFineChange:'update1(this)'}\" ";
  char hex[10];
  sprintf(hex,"%02X%02X%02X",redString[0].toInt(),greenString[0].toInt(),blueString[0].toInt());
  webSite += "value=\"" + String(hex) + "\"><br>";
  webSite += "WHITE LEDS<br>";
  sprintf(hex,"%i",whiteString[0].toInt());
  webSite += "<input type=\"range\" onchange=\"updateWhite1(this)\" id=\"whiteval1\" min=\"0\" max=\"256\" value=\"" + String(hex) + "\" step=\"1\" class=\"slider\"><span id=\"textwhiteval1\">%WHITEVALUE1%</span></p>\n";
  
  webSite += "<b>ENDEAVOR:</b><br>";
  webSite += "<p>RGB LEDS<br>";
  webSite += "<input id=\"picker2\" class=\"jscolor {closable:true,closeText:'Close me!',onFineChange:'update2(this)'}\" ";
  sprintf(hex,"%02X%02X%02X",redString[1].toInt(),greenString[1].toInt(),blueString[1].toInt());
  webSite += "value=\"" + String(hex) + "\"><br>";
  webSite += "WHITE LEDS<br>";
  sprintf(hex,"%i",whiteString[1].toInt());
  webSite += "<input type=\"range\" onchange=\"updateWhite2(this)\" id=\"whiteval2\" min=\"0\" max=\"256\" value=\"" + String(hex) + "\" step=\"1\" class=\"slider\"><span id=\"textwhiteval2\">%WHITEVALUE2%</span></p>\n";
// &#37
  
  webSite += "<b>CHURCH:</b><br>";
  webSite += "<p>RGB LEDS<br>";
  webSite += "<input id=\"picker3\" class=\"jscolor {closable:true,closeText:'Close me!',onFineChange:'update3(this)'}\" ";
  sprintf(hex,"%02X%02X%02X",redString[2].toInt(),greenString[2].toInt(),blueString[2].toInt());
  webSite += "value=\"" + String(hex) + "\"><br>";
  webSite += "WHITE LEDS<br>";
  sprintf(hex,"%i",whiteString[2].toInt());
  webSite += "<input type=\"range\" onchange=\"updateWhite3(this)\" id=\"whiteval3\" min=\"0\" max=\"256\" value=\"" + String(hex) + "\" step=\"1\" class=\"slider\"><span id=\"textwhiteval3\">%WHITEVALUE3%</span></p>\n";
  
  webSite += "<button onclick=\"saveall()\">SAVE</button>   ";
  webSite += "<button onclick=\"restoreall()\">RESTORE</button>";
  //webSite += "<button onclick=\"window.location.href='/SAVE';\">SAVE</button>";
  //webSite += "<button onclick=\"window.location.href='/RESTORE';\">RESTORE</button>";
  webSite += "<p></p><p>Created by Endeavor Labs</p>";
  
  webSite += "<script>\n";
  webSite += "xmlHttp=createXmlHttpObject();\n";

  webSite += "function createXmlHttpObject(){\n";
  webSite += "  if(window.XMLHttpRequest){\n";
  webSite += "    xmlHttp=new XMLHttpRequest();\n";
  webSite += "  }else{\n";
  webSite += "    xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n";
  webSite += "  }\n";
  webSite += "  return xmlHttp;\n";
  webSite += "}\n";
  
  webSite += "function update1(picker)\n";
  webSite += "{\n";
  webSite += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  webSite += "    xmlHttp.open('PUT','setLED1?r=' + Math.round(picker.rgb[0]) + '&g=' +  Math.round(picker.rgb[1]) + '&b=' + Math.round(picker.rgb[2]),true);\n";
  webSite += "    xmlHttp.send(null);\n";
  webSite += "  }\n";
  webSite += "}\n";
  
  webSite += "function update2(picker)\n";
  webSite += "{\n";
  webSite += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  webSite += "    xmlHttp.open('PUT','setLED2?r=' + Math.round(picker.rgb[0]) + '&g=' +  Math.round(picker.rgb[1]) + '&b=' + Math.round(picker.rgb[2]),true);\n";
  webSite += "    xmlHttp.send(null);\n";
  webSite += "  }\n";
  webSite += "}\n";
  
  webSite += "function update3(picker)\n";
  webSite += "{\n";
  webSite += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  webSite += "    xmlHttp.open('PUT','setLED3?r=' + Math.round(picker.rgb[0]) + '&g=' +  Math.round(picker.rgb[1]) + '&b=' + Math.round(picker.rgb[2]),true);\n";
  webSite += "    xmlHttp.send(null);\n";
  webSite += "  }\n";
  webSite += "}\n";

  webSite += "function updateWhite1(element)\n";
  webSite += "{\n";
  webSite += "  var sliderValue = document.getElementById(\"whiteval1\").value;\n";
  webSite += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  webSite += "    xmlHttp.open('PUT','setWHITE1?w=' + sliderValue,true);\n";
  webSite += "    xmlHttp.send(null);\n";
  webSite += "  }\n";
  webSite += "  document.getElementById(\"textwhiteval1\").innerHTML = sliderValue;\n";
  webSite += "}\n";

  webSite += "function init()\n";
  webSite += "{\n";
  webSite += "  var sliderValue = document.getElementById(\"whiteval1\").value;\n";
  webSite += "  document.getElementById(\"textwhiteval1\").innerHTML = sliderValue;\n";
  webSite += "  sliderValue = document.getElementById(\"whiteval2\").value;\n";
  webSite += "  document.getElementById(\"textwhiteval2\").innerHTML = sliderValue;\n";
  webSite += "  sliderValue = document.getElementById(\"whiteval3\").value;\n";
  webSite += "  document.getElementById(\"textwhiteval3\").innerHTML = sliderValue;\n";
  webSite += "}\n";

  webSite += "function updateWhite2(element)\n";
  webSite += "{\n";
  webSite += "  var sliderValue = document.getElementById(\"whiteval2\").value;\n";
  webSite += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  webSite += "    xmlHttp.open('PUT','setWHITE2?w=' + sliderValue,true);\n";
  webSite += "    xmlHttp.send(null);\n";
  webSite += "  }\n";
  webSite += "  document.getElementById(\"textwhiteval2\").innerHTML = sliderValue;\n";
  webSite += "}\n";

  webSite += "function updateWhite3(element)\n";
  webSite += "{\n";
  webSite += "  var sliderValue = document.getElementById(\"whiteval3\").value;\n";
  webSite += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  webSite += "    xmlHttp.open('PUT','setWHITE3?w=' + sliderValue,true);\n";
  webSite += "    xmlHttp.send(null);\n";
  webSite += "  }\n";
  webSite += "  document.getElementById(\"textwhiteval3\").innerHTML = sliderValue;\n";
  webSite += "}\n";
  
  webSite += "function saveall()\n";
  webSite += "{\n";
  webSite += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  webSite += "    xmlHttp.open('PUT','SAVE',true);\n";
  webSite += "    xmlHttp.send(null);\n";
  webSite += "  }\n";
  webSite += "}\n";
  
  webSite += "function restoreall()\n";
  webSite += "{\n";
  webSite += "  if(xmlHttp.readyState==0||xmlHttp.readyState==4){\n";
  webSite += "    xmlHttp.open('PUT','RESTORE',true);\n";
  webSite += "    xmlHttp.send(null);\n";
  webSite += "  }\n";
  webSite += "  setTimeout(() => {\n";
  webSite += "  location.reload();\n";
  webSite += "  },200);\n";
  webSite += "}\n";
  
  webSite += "</script>\n";
  webSite += "</BODY>\n";
  webSite += "</HTML>\n";
  
}
