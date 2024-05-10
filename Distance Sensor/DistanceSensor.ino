#include <LiquidCrystal.h>
int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int trig = 5; int echo = 6; int buzzerPin = 10;
byte customChar[] = {
  B00000,
  B00000,
  B00100,
  B00110,
  B00110,
  B01110,
  B11111,
  B11111
};
long getDistance(){
  pinMode(trig, OUTPUT);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo, HIGH);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin(16, 02);
  lcd.createChar(1, customChar);
  String title = "ULTRA_SONIC";
  lcd.setCursor((16-title.length())/2, 0);
  lcd.print(title);
  lcd.setCursor(0, 1);
  lcd.write(1);
  lcd.print("Dis:");
}

int distance = 0; //cm

void loop() {
  // put your main code here, to run repeatedly:
  distance = 0.0168*getDistance();
  lcd.setCursor(6, 1);
  lcd.print("                               ");
  lcd.setCursor(6, 1);
  lcd.print(distance);
  
  if(distance<4||distance>40)
  {
    delay(500);
  }
  else{
    tone(buzzerPin, 5000, 100);
    delay(distance*5);
  }
  
} 2