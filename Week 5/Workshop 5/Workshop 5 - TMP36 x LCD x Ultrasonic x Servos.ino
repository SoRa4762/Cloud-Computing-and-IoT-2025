#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// instanciating
Servo myServo1; // for temperature sensor
Servo myServo2; // for ultrasonic sensor
LiquidCrystal_I2C lcd1(0x27, 16, 2); // for temperature sensor
LiquidCrystal_I2C lcd2(0x26, 16, 2); // for ultrasonic sensor

// global variable
int lastAngle1 = 79;
int lastAngle2 = -1;
int echoPin = 3;
int trigPin = 4;

void setup()
{
  // serial communication
  Serial.begin(9600);
  
  // pin setups
  pinMode(A0, INPUT);
  myServo1.attach(6);
  myServo2.attach(5);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // lcd1 setup
  lcd1.init();
  lcd1.backlight();
  lcd1.setCursor(0, 0);
  lcd1.print("Ohayo Sekai- 1!");
  
  // lcd2 setup
  lcd2.init();
  lcd2.backlight();
  lcd2.setCursor(0, 0);
  lcd2.print("Ohayo Sekai - 2!");
  
}

void loop()
{
  // function calls - LCD x Servo
  displayTemp();
  rotateServo1();
  
  // for ultrasonic x servo
  displayDistance();
  rotateServo2();
}

// temp calc function
float tempCFn(){
  float analogValue = analogRead(A0);
  float voltageOut = analogValue * (5/1024.0);
  float tempC = (voltageOut - 0.5) * 100;
  
  Serial.println("Temp in C: " + String(tempC));
  return tempC;
}

// temp display function
void displayTemp(){
  lcd1.setCursor(0, 1);
  lcd1.print("Temp in C: ");
  lcd1.print(tempCFn());
  lcd1.print(" C");
}

// rotate servo 1 according to TMP36
void rotateServo1(){
  int newAngle;
  float tempC = tempCFn();
  Serial.println("Temp from Servo: " + String(tempC));

  if(tempC < 20){
    newAngle = 0;
  } 
  else if(tempC >= 20 && tempC < 40){
    newAngle = 90;
  } 
  else {
    newAngle = 180;
  }

  // update last angle with new one
  if (newAngle != lastAngle1) {
    lcd1.clear();               
    myServo1.write(newAngle);   
    lastAngle1 = newAngle;      

    // display in lcd
    lcd1.setCursor(0, 0);
    lcd1.print("Servo to ");
    lcd1.print(newAngle);
    lcd1.print("!");
  }
}

// find distance
float checkDistance(){
  digitalWrite(trigPin, LOW);
  delay(10);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration/2 * 0.034; // 0.034 = speed of sound
  return distance;
}

// display distance
void displayDistance(){
  lcd2.setCursor(0, 1);
  lcd2.print("Distance: ");
  lcd2.print(checkDistance());
  lcd2.print(" cm");
}

// rotate 2nd servo motor according to distance
void rotateServo2(){
  int newAngle;
  float dist = checkDistance();
  Serial.println("Distance from Ultrasonic Sensor: " + String(dist));

  if(dist < 50){
    newAngle = 0;
  } 
  else if(dist >= 50 && dist < 150){
    newAngle = 90;
  } 
  else {
    newAngle = 180;
  }

  // update last angle with new one
  if (newAngle != lastAngle2) {
    lcd2.clear();               
    myServo2.write(newAngle);   
    lastAngle2 = newAngle;      

    // display in lcd
    lcd2.setCursor(0, 0);
    lcd2.print("Servo to ");
    lcd2.print(newAngle);
    lcd2.print("!");
  }
}
