void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.println("Ohayo Sekai!");
}

void loop()
{
  //Serial.println("Good Morning World!");
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(7, HIGH);
  Serial.println("LED ON!");
  delay(1000); // Wait for 1000 millisecond(s)
  
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(7, LOW);
  Serial.println("LED OFF!");
  delay(1000); // Wait for 1000 millisecond(s)
}