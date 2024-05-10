#include "LiquidCrystal.h"

int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int buzzer = 11;

float setTemp = 34.00;


void setup(){
  pinMode(buzzer, OUTPUT);
  lcd.begin(16,02);
  lcd.setCursor(0,0);
  lcd.print("Set Temp: ");
  lcd.setCursor(11,0);
  lcd.print(setTemp);
}

float ar_temp[4] = {0.00,0.00,0.00,0.00};
int i = 0;
float temp = 0.00;

void loop(){
  float adcVal = analogRead(A0);
  float t = (adcVal * 500)/ 1023;
  
  ar_temp[i] = t;
  if(i >= 3){
    i = 0;
    temp = (ar_temp[0] + ar_temp[1] + ar_temp[2] + ar_temp[3]) / 4 - 49;
    
  }
  i++;
  
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.setCursor(6,1);
  lcd.print("      ");
  lcd.setCursor(6,1);
  lcd.print(temp);
  
  if(temp > setTemp) {
    tone(buzzer, 5000, 100);
    
  } else if(temp <= setTemp) {
  }
  
  
}