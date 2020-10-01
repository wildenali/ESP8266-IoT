#include <ESP8266WiFi.h>

const char* ssid = "wildenali";      // Nama AP/Hotspot
const char* password = "wildenali123";    // Password AP/Hotspot

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  
 // Mengatur WiFi ----------------------------------------------------------
  Serial.print("Configuring access point..."); 
  WiFi.mode(WIFI_AP);             // Mode AP/Hotspot
  WiFi.softAP(ssid, password);
  
 // Start the server -------------------------------------------------------
  server.begin();
  Serial.println("Server dijalankan");
   
 // Print the IP address ---------------------------------------------------
  Serial.println(WiFi.localIP());
 }

void loop() {
  // put your main code here, to run repeatedly:

}
