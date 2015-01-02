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
}

void loop() {

  
}

