// C++ code
//
int counter;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  for (counter = 0; counter < 10; ++counter) {
    analogWrite(11, 255);
    analogWrite(10, 255);
    analogWrite(9, 51);
    delay(2000); // Wait for 2000 millisecond(s)
    analogWrite(11, 255);
    analogWrite(10, 0);
    analogWrite(9, 0);
    delay(2000); // Wait for 2000 millisecond(s)
  }
}