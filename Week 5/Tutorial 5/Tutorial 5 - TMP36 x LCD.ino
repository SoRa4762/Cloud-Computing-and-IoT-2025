#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Instanciate
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Konnichiwa!");
}

void loop()
{
  float analogValue = analogRead(A0);
  //Serial.println("Analog Value: " + String(analogValue));
  float voltageOut = analogValue * (5/1023.0);
  float tempC = (voltageOut - 0.5) * 100;
  Serial.println("Temp in C: " + String(tempC));
  
  lcd.setCursor(0, 1);
  lcd.print("Temp in C: ");
  lcd.print(tempC);
}