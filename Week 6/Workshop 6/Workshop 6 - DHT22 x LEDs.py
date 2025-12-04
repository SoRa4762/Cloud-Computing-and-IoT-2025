from machine import Pin
import time
import dht

dht_sensor_pin = Pin(2)
dht_sensor = dht.DHT22(dht_sensor_pin)

red_led_pin = Pin(0, Pin.OUT)
yellow_led_pin = Pin(4, Pin.OUT)
green_led_pin = Pin(16, Pin.OUT)

while True:
    try:
        # read data
        dht_sensor.measure()
        tempC = dht_sensor.temperature()
        hum = dht_sensor.humidity()

        # print data
        print("Temperature: {:.1f} °C".format(tempC))
        print("Humidity: {:.1f} %".format(hum))

        # blink LED - the logic ands should be at the top and or should be in the bottom
        if(tempC < 35 and hum > 50):
            green_led_pin.on()
            red_led_pin.off()
            yellow_led_pin.off()
        elif(tempC > 35 and hum < 40):
            yellow_led_pin.on()
            red_led_pin.off()
            green_led_pin.off()
        elif(tempC > 40 or hum < 50):
            red_led_pin.on()
            green_led_pin.off()
            yellow_led_pin.off()

    except OSError as e:
        print("Error reading DHT22 sensor's data: ", e)

    time.sleep(2)