# MQTT Broker, Publisher and Subscriber

## `Broker`
Install Mosquitto</br>
- Referensi dari http://jaza.li/mqtt/cara-instal-mosquitto-pada-windows-os/
- Test mosquitto broker
    - Go to mosquitto folder
        `$ cd c:\Program Files\mosquitto`
    - Run mosquitto
        `$ mosquitto.exe`
    - Run Subscriber
        `$ mosquitto_sub -h localhost -t initopic/wilden/Sensor1 -v`
    - Run Publisher
        `$ mosquitto_pub -h localhost -p 1883 -t initopic/wilden/Sensor1 -m 32`
    - Close the terminal

## `Publisher and Subscriber NodeJS`
0. Create package.js file `$ npm init`
1. Install node_modules `$ npm i`
2. Install mqtt nodejs `$ npm i mqtt`
3. Create a new publisher nodejs file named `pub.js`
    ```sh
    // MQTT publisher
    var mqtt = require('mqtt')
    var client = mqtt.connect('mqtt://localhost:1883')
    var topic = 'initopic/wilden/Sensor1'
    var message = '0'
    var nambah = 0;

    client.on('connect', ()=>{
        setInterval(()=>{
            nambah++;
            if (nambah >= 10) {
                nambah = 0
            }
            message = nambah.toString();
            client.publish(topic, message)
            console.log('Message sent!', message)
        }, 100)
    })
    ```
4. Create a new subscriber nodejs file named `sub.js`
    ```sh
    // MQTT subscriber
    var mqtt = require('mqtt')
    var client = mqtt.connect('mqtt://localhost:1883')
    var topic = 'initopic/wilden/Sensor1'

    client.on('message', (topic, message)=>{
        message = message.toString()
        console.log(message)
    })

    client.on('connect', ()=>{
        client.subscribe(topic)
    })
    ```
5. Run the pub.js and sub.js
    - Run the mosquitto broker, go to mosquitto folder
        `$ cd c:\Program Files\mosquitto`
        `$ mosquitto.exe`
    - Open a new terminal, go to your folder project and run pub.js
        `$ node pub.js`
    - Open a new terminal, go to your folder project and run sub.js
        `$ node sub.js`

## `Publisher NodeJS and Subscriber Arduino`
1. Create a new Subscriber arduino file named `sub.ino`
    ```sh
    #include <ESP8266WiFi.h>
    #include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

    // WiFi, Make sure to update this for your own WiFi network!
    const char* ssid = "ROBOTIC";
    const char* wifi_password = "CRazytoy!@#123";

    // MQTT, Make sure to update this for your own MQTT Broker!
    const char* mqtt_server = "192.168.88.240";
    const char* mqtt_topic = "initopic";
    const char* clientID = "message";

    // Initialise the WiFi and MQTT Client objects
    WiFiClient wifiClient;
    PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

    void ReceivedMessage(char* topic, byte* payload, unsigned int length) {
        // Output the first character of the message to serial (debug)
        Serial.print((char)payload[0]);
        Serial.println();
    }

    bool Connect() {
    // Connect to MQTT Server and subscribe to the topic
    if (client.connect(clientID)) {
            client.subscribe(mqtt_topic);
            return true;
        }
        else {
            return false;
        }
    }

    void setup() {
        Serial.begin(115200);
        
        Serial.print("Connecting to ");
        Serial.println(ssid);
        WiFi.begin(ssid, wifi_password);

        // Wait until the connection has been confirmed before continuing
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }

        // Debugging - Output the IP Address of the ESP8266
        Serial.println("WiFi connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());

        // Connect to MQTT Broker, setCallback sets the function to be called when a message is received.
        client.setCallback(ReceivedMessage);
        if (Connect()) {
            Serial.println("Connected Successfully to MQTT Broker!");  
        }
        else {
            Serial.println("Connection Failed!");
        }
    }

    void loop() {
        // If the connection is lost, try to connect again
        if (!client.connected()) {
            Connect();
        }
        // client.loop() just tells the MQTT client code to do what it needs to do itself (i.e. check for messages, etc.)
        client.loop();
        // Once it has done all it needs to do for this cycle, go back to checking if we are still connected.
    }
    ```
2. Change the IP mqtt_server
    - Open a new terminal
    - Type `ipconfig`
    - Open a `sub.ino` file and change the IP mqtt_server with yout server IP
        `const char* mqtt_server = "192.168.88.240";`
3. Run the pub.js and sub.ino
    - Run the mosquitto broker, go to mosquitto folder
        `$ cd c:\Program Files\mosquitto`
        `$ mosquitto.exe`
    - Open a new terminal, go to your folder project and run pub.js
        `$ node pub.js`
    - Open a sub.ino with Arduino IDE and click Serial Monitor Icon

## `Publisher and Subscriber Python`
1. Install paho mqtt on python project `$ pip install paho-mqtt`
2. Create a new publisher python file named `pub.py`
    ```sh
    # publisher
    import paho.mqtt.client as mqtt
    from time import sleep

    client = mqtt.Client()
    client.connect('localhost', 1883)

    x = 10

    while True:
        x += 1
        if(x >= 20):
            x = 10
        print(x)
        sleep(0.01)
        client.publish('initopic_rpi', x)
    ```
3. Create a new subscriber python file named `sub.py`
    ```sh
    # subscriber
    import paho.mqtt.client as mqtt
    
    client = mqtt.Client()
    client.connect('localhost', 1883)

    def on_connect(client, userdata, flags, rc):
        print("Connected to broker!")
        client.subscribe("initopic_rpi")
    
    def on_message(client, userdata, message):
        print(message.payload.decode())

    while True:
        client.on_connect = on_connect
        client.on_message = on_message
        client.loop_forever()
    ```
4. Run the pub.js and sub.js
    - Run the mosquitto broker, go to mosquitto folder
        `$ cd c:\Program Files\mosquitto`
        `$ mosquitto.exe`
    - Open a new terminal, go to your folder project and run pub.py
        `$ python pub.py`
    - Open a new terminal, go to your folder project and run sub.py
        `$ python sub.py`
