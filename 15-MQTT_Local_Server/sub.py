# subscriber
import paho.mqtt.client as mqtt

client = mqtt.Client()
client = connect('localhost', 1883)

def on_connect(client, userdata, flags, rc):
    print("Connected to broker!")
    client.subscribe("initopic_rpi")

def on_message(client, userdata, message):
    print(message.payload.decode())

while True:
    client.on_connect = on_connect
    client.on_message = on_message
    client.loop_forever()