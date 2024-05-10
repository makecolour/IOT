// C++ code
//
int animationSpeed = 0;
int totalLight = 0;

void setup()
{
  totalLight = 8;
  animationSpeed = 400;
  
  for(int i = 0; i < totalLight; i++)
  {
    pinMode(i+6, OUTPUT);
  }
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(animationSpeed); // Wait for animationSpeed millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(animationSpeed); // Wait for animationSpeed millisecond(s)
  
  for(int i = 0; i < totalLight; i++)
  {
    digitalWrite(i+6, HIGH);
    delay(animationSpeed); // Wait for animationSpeed millisecond(s)
    digitalWrite(i+6, LOW);
  }
    
    
}