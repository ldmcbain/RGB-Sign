#include "./myeeprom.h"


StoredSettings romSettings;



/**
 * Retrieves stored settings from EEPROM so that WiFi setup does not have to be repeated on every power cycle
 * 
 * @return struct
 * @author costmo
 * @since  20180929
 */
StoredSettings getStoredSettings()
{
  uint addr = 0;
  EEPROM.begin( 512 );
  EEPROM.get( addr, romSettings );
  EEPROM.end();
  itoa(constrain(atoi(romSettings.RD1),0,255),romSettings.RD1,10);
  itoa(constrain(atoi(romSettings.GR1),0,255),romSettings.GR1,10);
  itoa(constrain(atoi(romSettings.BL1),0,255),romSettings.BL1,10);
  itoa(constrain(atoi(romSettings.WH1),0,255),romSettings.WH1,10);
  itoa(constrain(atoi(romSettings.RD2),0,255),romSettings.RD2,10);
  itoa(constrain(atoi(romSettings.GR2),0,255),romSettings.GR2,10);
  itoa(constrain(atoi(romSettings.BL2),0,255),romSettings.BL2,10);
  itoa(constrain(atoi(romSettings.WH2),0,255),romSettings.WH2,10);
  itoa(constrain(atoi(romSettings.RD3),0,255),romSettings.RD3,10);
  itoa(constrain(atoi(romSettings.GR3),0,255),romSettings.GR3,10);
  itoa(constrain(atoi(romSettings.BL3),0,255),romSettings.BL3,10);
  itoa(constrain(atoi(romSettings.WH3),0,255),romSettings.WH3,10);
  /*
  Serial.println("EEPROM c_str RESTORE values:");
  Serial.printf("R1:%s G1:%s B1:%s W1:%s ",romSettings.RD1,romSettings.GR1,romSettings.BL1,romSettings.WH1);
  Serial.printf("R2:%s G2:%s B2:%s W2:%s ",romSettings.RD2,romSettings.GR2,romSettings.BL2,romSettings.WH2);
  Serial.printf("R3:%s G3:%s B3:%s W3:%s ",romSettings.RD3,romSettings.GR3,romSettings.BL3,romSettings.WH3);
  Serial.println("");
  */
  return romSettings;
}


/**
 * Stores the input settings to EEPROM
 * 
 * @return void
 * @author costmo
 * @since  20180929
 */
void saveSettings(String r1, String g1, String b1, String w1, String r2, String g2, String b2, String w2, String r3, String g3, String b3, String w3)
{
  uint addr = 0;

  strcpy( romSettings.RD1, r1.c_str() );
  strcpy( romSettings.GR1, g1.c_str() );
  strcpy( romSettings.BL1, b1.c_str() );
  strcpy( romSettings.WH1, w1.c_str() );
  strcpy( romSettings.RD2, r2.c_str() );
  strcpy( romSettings.GR2, g2.c_str() );
  strcpy( romSettings.BL2, b2.c_str() );
  strcpy( romSettings.WH2, w2.c_str() );
  strcpy( romSettings.RD3, r3.c_str() );
  strcpy( romSettings.GR3, g3.c_str() );
  strcpy( romSettings.BL3, b3.c_str() );
  strcpy( romSettings.WH3, w3.c_str() );
/*
  Serial.println("EEPROM c_str values:");
  Serial.printf("R1:%s G1:%s B1:%s W1:%s ",romSettings.RD1,romSettings.GR1,romSettings.BL1,romSettings.WH1);
  Serial.printf("R2:%s G2:%s B2:%s W2:%s ",romSettings.RD2,romSettings.GR2,romSettings.BL2,romSettings.WH2);
  Serial.printf("R3:%s G3:%s B3:%s W3:%s ",romSettings.RD3,romSettings.GR3,romSettings.BL3,romSettings.WH3);
  Serial.println("");
*/
  EEPROM.begin( 512 );
  EEPROM.put( addr, romSettings );
  EEPROM.end();
}
