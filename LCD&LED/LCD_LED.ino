#include <LiquidCrystal.h>

int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8, led_pin = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6,d7);

byte sun[] = {
  B00000,
  B10101,
  B01110,
  B11011,
  B01110,
  B10101,
  B00000,
  B00000
};

byte moon[] = {
  B00000,
  B01111,
  B11100,
  B11000,
  B11000,
  B11100,
  B01111,
  B00000
};
byte lightOn[] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B11111,
  B11111,
  B01010,
  B01010
};
byte lightOff[] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
  B01010,
  B01010
};

// C++ code
//
void setup()
{
  pinMode(led_pin, OUTPUT);
  lcd.begin(16, 02);
  lcd.createChar(1, sun);
  lcd.createChar(2, moon);
  lcd.createChar(3, lightOn);
  lcd.createChar(4, lightOff);
  lcd.setCursor(4, 0);
  lcd.print("Chillin'");
}

void loop()
{
  int adc = analogRead(A0);
  lcd.setCursor(0, 1);
  lcd.print("                        ");
  lcd.setCursor(0, 1);
  if(adc<600)
  {
    lcd.write(1);
    lcd.print("ADC: ");
    lcd.print(adc);
    lcd.print(" ");
    lcd.write(3);
    lcd.print("OFF");
    digitalWrite(led_pin, LOW);
  }
  else
  {
    lcd.write(2);
    lcd.print("ADC: ");
    lcd.print(adc);
    lcd.print(" ");
    lcd.write(4);
    lcd.print("ON");
    digitalWrite(led_pin, HIGH);
  }
  delay(50);
  digitalWrite(led_pin, LOW);
}