void setup()
{
  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
}

void loop()
{
  // read pull down button state
  int pullDownState = digitalRead(8);
  Serial.print("Pull Down State: ");
  Serial.println(pullDownState);
  
  //read pull up button state
  int pullUpState = digitalRead(9);
  Serial.print("Pull Up State: ");
  Serial.println(pullUpState);
  
  // LED Control
  if(pullDownState == HIGH){
    digitalWrite(7, HIGH);
    Serial.println("LED ON!");
  } else {
    digitalWrite(7, LOW);
    Serial.println("LED OFF!");
  }
  
  delay(1000);
  
  //digitalWrite(LED_BUILTIN, HIGH);
  //delay(1000); // Wait for 1000 millisecond(s)
  //digitalWrite(LED_BUILTIN, LOW);
  //delay(1000); // Wait for 1000 millisecond(s)
}