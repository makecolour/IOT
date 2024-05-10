#include "LiquidCrystal.h"

int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

byte sun_icon[] = {
  B00000,
  B10101,
  B01110,
  B11111,
  B01110,
  B10101,
  B00000,
  B00000
};

byte led_icon[] = {
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
  B01110,
  B11111,
  B01010
};


int led_pin = 10;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Chillin Studio");
  lcd.createChar(1, sun_icon);
  lcd.setCursor(0,1);
  lcd.write(1);
  lcd.setCursor(2,1);
  lcd.print("ADC: ");
  
  
  lcd.createChar(10,led_icon);
  lcd.setCursor(10,1);
  lcd.write(10);

}

void loop() {
  int adc_val = analogRead(A0);
  lcd.setCursor(6,1);
  lcd.print("    ");
  lcd.setCursor(6,1);
  lcd.print(adc_val);
    
  lcd.setCursor(11,1);
  lcd.print("    ");
  if(adc_val >= 86) 
  {
    lcd.setCursor(11,1);
    digitalWrite(led_pin, HIGH);
    lcd.write("ON");
  } else if (adc_val < 86) {
    lcd.setCursor(11,1);
    digitalWrite(led_pin, LOW);
    lcd.write("OFF");
  }
                  
  delay(100);
}