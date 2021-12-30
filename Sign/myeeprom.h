#ifndef _MYEEPROMH_
#define _MYEEPROMH_

#include <EEPROM.h>
#include <Arduino.h>

// Values saved to EEPROM for persistent storage of settings
struct StoredSettings
  {
    char RD1[8];
    char GR1[8];
    char BL1[8];
    char WH1[8];
    char RD2[8];
    char GR2[8];
    char BL2[8];
    char WH2[8];
    char RD3[8];
    char GR3[8];
    char BL3[8];
    char WH3[8];
  };

extern StoredSettings romSettings;

StoredSettings getStoredSettings();
//void wipeSettings();
void saveSettings(String r1, String g1, String b1, String w1, String r2, String g2, String b2, String w2, String r3, String g3, String b3, String w3);

#endif
