import network
import time
import ujson
import dht
from machine import Pin
from umqtt.simple import MQTTClient

# WiFi variables
ssid = "Wokwi-GUEST"
password = ""

# MQTT variables
MQTT_CLIENT_ID = "YOUR_CLIENT_ID"
MQTT_BROKER = "YOUR_BROKER"
MQTT_USER = "YOUR_USERNAME"
MQTT_PASS = "YOUR_PASSWORD"
MQTT_SSL = True
MQTT_PORT = 8883
MQTT_TOPIC1 = "YOUR/TOPIC1"
MQTT_TOPIC2 = "YOUR/TOPIC2"

# global variables
client = None
led_state = None

# setup led
led_pin = Pin(2, Pin.OUT)

# sensors
dht_sensor = dht.DHT22(Pin(15))

# callback
def set_cb(topic, msg):
    received_topic = topic.decode()
    received_msg = msg.decode()

    print(f"Following message: {received_msg} received in the topic: {received_topic}")
    # add control logic after you receive certain instruction from the NODERED UI buttons
    if(received_topic == "IOT/LED/State"):
        print(f"LED State: {received_msg}")
        if(received_msg == "ON"):
            led_pin.value(1)
        else:
            led_pin.value(0)

# Connect to WiFi
def connect_wifi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)
    print("WiFi is connecting...")

    while not wlan.isconnected():
        print(".")
        time.sleep(0.1)
    print("Connected to WiFi: ", ssid)
    print("More info: ", wlan.ifconfig())

# Connect to MQTT - HiveMQ
def connect_mqtt():
    client = MQTTClient(
        client_id=MQTT_CLIENT_ID,
        server=MQTT_BROKER,
        port=MQTT_PORT,
        user=MQTT_USER,
        password=MQTT_PASS,
        ssl=MQTT_SSL,
        ssl_params={"server_hostname": MQTT_BROKER}
    )
    client.connect()
    print("Connecting to MQTT...")
    return client

# setup
try:
    connect_wifi()
    client = connect_mqtt()
    # trigger callback
    client.set_callback(set_cb)
    client.subscribe(MQTT_TOPIC1)
    client.subscribe(MQTT_TOPIC2)
    print(f"Subscribed to Topic: {MQTT_TOPIC1}")

except Exception as e:
    print("Error in the setup process: ", e)

# loop
try:
    while True:
        # measure sensor
        dht_sensor.measure()

        # json data
        ujsonDumps = ujson.dumps({
            "temperature": dht_sensor.temperature(),
            "humidity": dht_sensor.humidity()
        })

        # check messages
        client.check_msg()
        
        # publish data
        client.publish(MQTT_TOPIC1, ujsonDumps)
        time.sleep(1)

except Exception as e:
    print("Error running the code block in MicroPython: ", e)
