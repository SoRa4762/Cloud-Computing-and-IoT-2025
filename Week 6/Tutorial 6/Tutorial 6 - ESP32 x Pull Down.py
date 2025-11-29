from machine import Pin
import time

led = Pin(4, Pin.OUT)
button_pin = Pin(0, Pin.IN)

def blinkLED():
    pushButtonState = button_pin.value()
    print(pushButtonState);
    
    if(pushButtonState == 1):
        led.value(1)
    else:
        led.off()

while True:
  blinkLED()