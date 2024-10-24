void setup()
{
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  analogWrite(7, 255);
  analogWrite(6, 0);
  analogWrite(5, 0);
  delay(1000); // Wait for 1000 millisecond(s)
  analogWrite(7, 255);
  analogWrite(6, 255);
  analogWrite(5, 102);
  delay(1000); // Wait for 1000 millisecond(s)
}