#include <LiquidCrystal.h>
#include <IRremote.h>
#include <Servo.h>

int irRemoteNumber[] = { 12, 16, 17, 18, 20, 21, 22, 24, 25, 26 };
int password[] = { 16, 17, 18, 20 };
int passwordLength = 4;
int start = 0;
int enteredPassword[10];

int irPin = 2;
int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


Servo myServo;

void setup() {
  IrReceiver.begin(irPin);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("     ");
  myServo.attach(10);
  myServo.write(0);

  IrReceiver.enableIRIn();
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print("Input:");
  if (IrReceiver.decode()) {
    int irDataIn = IrReceiver.decodedIRData.command;

    // Check if the entered password length reaches the predefined length
    if (start < passwordLength) {
      enteredPassword[start] = irDataIn;

      // Print '*' to represent the entered password digits
      lcd.setCursor(start + 7, 1); // Adjust the starting position according to the length of "Input:"
      lcd.print('*');
      start++;
    }

    // Verify password if the length is equal to the predefined length
    if (start >= passwordLength) {
      // Check if the entered password is correct
      bool correctPassword = true;
      for (int i = 0; i < passwordLength; i++) {
        if (enteredPassword[i] != password[i]) {
          correctPassword = false;
          break;
        }
      }
      if (correctPassword) {
        lcd.setCursor(0, 0);
        lcd.print("  Correct");
        tone(buzzerPin, 5000, 100);
        digitalWrite(led_pin, HIGH);
        delay(2000);
        digitalWrite(led_pin, LOW);

        // Clear "Correct" message
        lcd.setCursor(0, 0);
        for (int i = 0; i < 9; i++) { // "Correct" has 7 characters
          lcd.print(" ");
        }
        lcd.setCursor(0, 1);
        for (int i = 0; i < passwordLength+8; i++) { // Adjust for "Input:" and password length
          lcd.print(" ");
        }
      } else {
        lcd.setCursor(0, 0);
        lcd.print("  Wrong");
        tone(buzzerPin, 5000, 100);
        digitalWrite(led_pin, HIGH);
        digitalWrite(led_pin, LOW);
        delay(1500);

        // Clear "Wrong" message
        lcd.setCursor(0, 0);
        for (int i = 0; i < 7; i++) { // "Wrong" has 5 characters
          lcd.print(" ");
        }
        lcd.setCursor(0, 1);
        for (int i = 0; i < passwordLength+8; i++) { // Adjust for "Input:" and password length
          lcd.print(" ");
        }
      }
      memset(enteredPassword, 0, sizeof(enteredPassword));
      start = 0;
    }

    IrReceiver.resume();
  }
}
