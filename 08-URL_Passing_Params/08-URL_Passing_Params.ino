#include <ESP8266WiFi.h>
 
const char* mySSID = "inimodulesp";      // Nama AP/Hotspot
const char* myPassword = "inimodulesp";    // myPassword AP/Hotspot
 
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
 // Seeting WiFi 
  Serial.print("Seeting WiFi as Access Point..."); 
  WiFi.mode(WIFI_AP);             // Mode AP/Hotspot
  WiFi.softAP(mySSID, myPassword);
  
 // Start the server -------------------------------------------------------
  server.begin();
  Serial.println("Server run");
  
 // Print the IP address ---------------------------------------------------
  Serial.println(WiFi.softAPIP());
 }

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Perintah yang diterima untuk menghidupkan led
  if (req.indexOf("LED1=ON") != -1)
      digitalWrite(LED_BUILTIN, LOW);
  else if (req.indexOf("LED1=OFF") != -1)
      digitalWrite(LED_BUILTIN, HIGH);
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
  
  client.flush();
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
