// C++ code
//
#define led_pin 2

void setup()
{
  pinMode(led_pin, OUTPUT);
  
  Serial.println("Done setup!");
  digitalWrite(led_pin, HIGH);
}

void loop()
{
  digitalWrite(led_pin, LOW);
  delay(1000);
  digitalWrite(led_pin, HIGH);
  delay(1000);
}