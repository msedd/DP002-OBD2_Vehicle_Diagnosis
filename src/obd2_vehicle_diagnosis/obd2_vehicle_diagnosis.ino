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


// OBD-II UART Adapter
COBD obd;

LiquidCrystal* lcd;
enum BtnKey {btnRIGHT, btnUP, btnDOWN, btnLEFT, btnSELECT, btnNONE};
int oldkey = btnNONE;


void setup() {
  lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
  lcd->clear();
  lcd->begin(16, 2);
  lcd->setCursor(0, 0);
  lcd->print("DP002:");
  lcd->setCursor(0, 1);
  lcd->print("Vehicle Diagn.");
  
   delay(1000);

  // starte Kommunikation mit dem OBD-II Adapter
  lcd->clear();
  lcd->setCursor(0, 1);
  lcd->print("Start connection...");
  
  obd.begin();
  while (!obd.init()){
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("init obd2 failed!");
    lcd->setCursor(0, 1);
    lcd->print("try again...");
    //delay(1000);
  }
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("init obd2 succeed");
  lcd->setCursor(0, 1);
  lcd->print("start diagnosis");

}

void onButtonClickCallBack(unsigned int buttonEvent){

  switch(buttonEvent){
   case btnRIGHT:
     break;
   case btnUP:
     break; 
   case btnDOWN: 
     break;
   case btnLEFT: 
     break;
   case btnSELECT: 
     break;
   case btnNONE:
     break;
  }

  
}
void readButtonValue() {

  int adc_key_in = analogRead(0);
  
  int key = transform(adc_key_in);
  if (key != oldkey) {
    delay(50);
    adc_key_in = analogRead(0);
    key = transform(adc_key_in);
    if (key != oldkey) {
      oldkey = key;
      if (key != btnNONE) {
        //debugEvent(adc_key_in);
        onButtonClickCallBack(key);
      }
    }
  }
}
int transform(unsigned int input) {
  if (input > 1000)		
    return btnNONE;
  else if (input < 50)
    return btnRIGHT;
  else if (input < 195)
    return btnUP;
  else if (input < 380)
    return btnDOWN;
  else if (input < 555)
    return btnLEFT;
  else if (input < 790)
    return btnSELECT;
  else
    return btnNONE;
}

void loop() {
  
  readButtonValue();
 
}
