#include <LiquidCrystal.h>
#include <IRremote.h>
#include <Servo.h>

#define TRIG_PIN 12
#define IR_PIN 2
#define ECHO_PIN 9
#define LED_PIN 13
#define SERVO_PIN 10
#define TEMP_SENSOR_PIN A0

// these signal numbers is noted based on real signal, not in tinkercad
int irRemoteNumber[] = { 22, 12, 24, 94, 8, 28, 90, 66, 82, 74 }; //1, 2, 3, 4, 5, 6, 7, 8, 9
int manual = 12;
int minTemp = 20;//25
int maxTemp = 29;//45
int maxDist = 15;
unsigned long breakTime = 15000;//28800000
unsigned long lastFeed;
unsigned long now;

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
Servo myServo;
float setTemp = 34.00;
float ar_temp[4] = {0.00, 0.00, 0.00, 0.00};
int tempIndex = 0;

byte dog[] = {
  B00000,
  B01100,
  B11100,
  B01111,
  B01111,
  B01010,
  B00000,
  B11111
};

byte danger[] = {
  B00000,
  B11011,
  B11011,
  B11011,
  B11011,
  B00000,
  B11011,
  B00000
};

void setup() {
  IrReceiver.begin(IR_PIN);
  lcd.createChar(1, dog);
  lcd.createChar(2, danger);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  lcd.begin(16, 2);
  myServo.attach(SERVO_PIN);
  myServo.write(0);
  IrReceiver.enableIRIn();
  Serial.begin(9600);
  lcd.setCursor(1, 0);
  lcd.print("Temp: ");
  lastFeed = millis();
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH);
}

float readTemp() {
  float adcVal = analogRead(TEMP_SENSOR_PIN);
  float t = (adcVal * 500) / 1023;
  
  ar_temp[tempIndex] = t;
  tempIndex = (tempIndex + 1) % 4;

  float tempSum = 0;
  for (int i = 0; i < 4; i++) {
    tempSum += ar_temp[i];
  }
  return (tempSum / 4);
}

void moveServo() {
  myServo.write(180);
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  myServo.write(0);
  digitalWrite(LED_PIN, LOW);
  lastFeed = millis();
}

void loop() {
  float temp = readTemp();
  int distance = 0.0168 * getDistance();
  lcd.setCursor(12, 0);
  lcd.print("              ");
  lcd.setCursor(12, 0);
  lcd.print(distance);

  now = millis();
  //Temperature
  lcd.setCursor(6,0);
  lcd.print(temp); 
  if(temp>maxTemp)
  {
    lcd.setCursor(0, 0);
    lcd.write(2);
  }
  else{
    lcd.setCursor(0, 0);
    lcd.write(1);
  }

  //Feeding
  if (IrReceiver.decode()) {
    int irDataIn = IrReceiver.decodedIRData.command;
    if(irDataIn==manual || distance > maxDist){
      moveServo();
    }
    
    IrReceiver.resume();
  }
  //Auto feed
  // if (distance > maxDist)
  // {
  //   moveServo();
  // }

  //Check last feed
  lcd.setCursor(0, 1);
  if(now - lastFeed > breakTime || temp > maxTemp)
  {
    lcd.print("                     ");
    lcd.setCursor(0, 1);
    lcd.print("Check your pet!");
  }
  else{
    lcd.print("                     ");
    lcd.setCursor(0, 1);
    lcd.print("Your pet is full!");
  }

  delay(1000);
}
