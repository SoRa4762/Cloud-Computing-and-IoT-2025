int trigPin = 7;
int echoPin = 8;
float duration;
float distance;
float speedOfSound = 0.034;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  Serial.print("Distance: ");
  Serial.print(checkDistance());
  Serial.println(" cm");
}

float checkDistance(){
  digitalWrite(trigPin, LOW);
  delay(10);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/2 * speedOfSound;
  return distance;
}