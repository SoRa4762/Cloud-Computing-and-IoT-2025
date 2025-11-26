#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// instanciating
Servo myServo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// global variable
int lastAngle = 79;

void setup()
{
  // serial communication
  Serial.begin(9600);
  
  // pin setups
  pinMode(A0, INPUT);
  myServo.attach(6);
  
  // lcd setup
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Ohayo Sekai!");
}

void loop()
{
  // function calls - LCD x Servo
  displayLCD();
  rotateServo();
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
void displayLCD(){
  lcd.setCursor(0, 1);
  lcd.print("Temp in C: ");
  lcd.print(tempCFn());
  lcd.print(" C");
}

void rotateServo(){
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
  if (newAngle != lastAngle) {
    lcd.clear();               
    myServo.write(newAngle);   
    lastAngle = newAngle;      

    // display in lcd
    lcd.setCursor(0, 0);
    lcd.print("Servo to ");
    lcd.print(newAngle);
    lcd.print("!");
  }
}
