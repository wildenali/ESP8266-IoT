# publisher
import paho.mqtt.client as mqtt
from time import sleep

client = mqtt.Client()
client = connect('localhost', 1883)

x = 10

while True:
    x += 1
    if(x >= 20):
        x = 10
    print(x)
    sleep(0.01)
    client.publish('initopic_rpi', x)