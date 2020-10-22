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