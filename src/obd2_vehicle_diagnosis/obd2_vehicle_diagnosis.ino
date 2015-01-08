
/*
  Developer Podcast 
 Folge: DP002-OBD2_Vehicle_Diagnosis
 
 Marko Seifert
 http://www.marko-seifert.de
 Apache 2 License
 
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <OBD.h>
#include <Wire.h>

COBD obd;

LiquidCrystal* lcd;

void updateDisplay(String str1, String str2){
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print(str1);
  lcd->setCursor(0, 1);
  lcd->print(str2);
}

void setup() {
  lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
  lcd->clear();
  lcd->begin(16, 2);
  updateDisplay("DP002:","Vehicle Diagn.");

  delay(1000);

  updateDisplay("Starting","try to connect...");
  obd.begin();
  while (!obd.init()){
    updateDisplay("init obd2 failed!","try again...");
  }
  updateDisplay("...successfully",getOBDStandard());
  delay(1000);

  String buffer;
  int value = 0;
  for(int i = 0; i < 4; i++){
    obd.read(0x20*i, value);
    buffer += String(value, HEX);
    buffer += " ";
  }

  updateDisplay("Supported PID",buffer);

  delay(3000);
}

void loop() {


  // PID_FUEL_LEVEL 0x2F
  int value = 0;
  //obd.read(PID_FUEL_LEVEL, value);
  //updateDisplay("Fuel level", String(value));

  // PID_SPEED 0x0D
  obd.read(PID_SPEED, value);
  String speed = String(value);
  // PID_RPM 0x0C
  obd.read(PID_RPM, value);
  String rpm = String(value);
  updateDisplay("Speed: "+speed +" km/h", "RPM: "+rpm + " rpm" );

  delay(1000);

}
String getOBDStandard(){

  int standard = 0;
  bool state = obd.read(0x1C, standard);
  String strStandard = "n.a.";

  if(!state){

    return strStandard;
  }

  switch(standard){
  case 1:
    strStandard = "OBD-II CARB";
    break;
  case 2:	
    strStandard = "OBD EPA";
    break;
  case 3:	
    strStandard = "OBD and OBD-II";
    break;
  case 4:	
    strStandard = "OBD-I";
    break;
  case 5:	
    strStandard = "Not OBD comp.";
    break;
  case 6:	
    strStandard = "EOBD (Europe)";
    break;
  case 7:	
    strStandard = "EOBD and OBD-II";
    break;
  case 8:	
    strStandard = "EOBD and OBD";
    break;
  case 9:	
    strStandard = "EOBD OBD OBD II";
    break;
  case 10:	
    strStandard = "JOBD (Japan)";
    break;
  case 11:	
    strStandard = "JOBD and OBD II";
    break;
  case 12:	
    strStandard = "JOBD and EOBD";
    break;
  case 13:	
    strStandard = "JOBD EOBD OBD II";
    break;
  case 14:	
    strStandard = "Reserved";
    break;
  case 15:	
    strStandard = "Reserved";
    break;
  case 16:	
    strStandard = "Reserved";
    break;
  case 17:	
    strStandard = "EMD";
    break;
  case 18:	
    strStandard = "EMD+";
    break;
  case 19:	
    strStandard = "HD OBD-C";
    break;
  case 20:	
    strStandard = "HD OBD";
    break;
  case 21:	
    strStandard = "WWH OBD";
    break;
  case 22:	
    strStandard = "Reserved";
    break;
  case 23:	
    strStandard = "HD EOBD-I";
    break;
  case 24:	
    strStandard = "HD EOBD-I N";
    break;
  case 25:	
    strStandard = "HD EOBD-II";
    break;
  case 26:	
    strStandard = "HD EOBD-II N";
    break;
  case 27:	
    strStandard = "Reserved";
    break;
  case 28:	
    strStandard = "OBDBr-1";
    break;
  case 29:	
    strStandard = "OBDBr-2";
    break;
  case 30:	
    strStandard = "KOBD";
    break;
  case 31:	
    strStandard = "IOBD I";
    break;
  case 32:	
    strStandard = "IOBD II";
    break;
  case 33:	
    strStandard = "HD EOBD-IV";
    break;
  default: 
    strStandard = "n.a.";
    break;
  }

  return strStandard;

}



