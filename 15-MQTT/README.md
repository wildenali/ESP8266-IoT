# MQTT

### Latiham MQTT Local Server

1. Download Mosquitto [https://mosquitto.org/download/](https://mosquitto.org/download/), download `mosquitto-1.6.12-install-windows-x64.exe`
2. Install mosquitto-1.6.12
3. Go to directory C:\Program Files\mosquitto
4. Double click `mosquitto.exe`
5. Run `$ mosquitto_sub.exe`:

- Open terminal atau cmd and go to C:\Program Files\mosquitto
- Type `$ mosquitto_sub.exe -h 127.0.0.1 -t test` and click Enter
  - h for Host
  - 127.0.0.1 for local IP
  - -t for topic
  - test for name of topic

6. Run `$ mosquitto_pub.exe`:

- Open terminal atau cmd and go to C:\Program Files\mosquitto
- Type `$ mosquitto_pub.exe -h 127.0.0.1 -t test -m "halooow"` and click Enter
  - h for Host
  - 127.0.0.1 for local IP
  - -t for topic
  - test for name of topic
  - -m for message
  - "helooow" for field of message
- Done and check in the mosquitto_sub.exe terminal

### Latiham MQTT with broker.mqtt-dashboard.com

1. Run `$ mosquitto_sub.exe`:

- Open terminal atau cmd and go to C:\Program Files\mosquitto
- Type `$ mosquitto_sub.exe -h broker.mqtt-dashboard.com -t wildentest` and click Enter
  - h for Host
  - broker.mqtt-dashboard.com for online broker
  - -t for topic
  - wildentest for name of topic

2. Run `$ mosquitto_pub.exe`:

- Open terminal atau cmd and go to C:\Program Files\mosquitto
- Type `$ mosquitto_pub.exe -h broker.mqtt-dashboard.com -t wildentest -m "halooow"` and click Enter
  - h for Host
  - broker.mqtt-dashboard.com for online broker
  - -t for topic
  - wildentest for name of topic
  - -m for message
  - "helooow" for field of message
- Done and check in the mosquitto_sub.exe terminal

## Install PubSubClient

1. Open Arduino IDE
2. Click Sketch > Include Library > Manage Libraries...
3. Type `pubsubclient` and install `pubsubclient` by Nick O'Leary. Click Close button if already done installed
4. Check on File > Examples > PubSubClient. If there means the installation was successful

References:

- [https://www.youtube.com/watch?v=MtMk6nChaW8](https://www.youtube.com/watch?v=MtMk6nChaW8)
- [https://doc.mapid.io/doc_iot/lets_code_cara_mengirimkan_data_melalui_komunikasi_mqtt_dengan_arduino_ide](https://doc.mapid.io/doc_iot/lets_code_cara_mengirimkan_data_melalui_komunikasi_mqtt_dengan_arduino_ide)
