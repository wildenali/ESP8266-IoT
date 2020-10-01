#include <ESP8266WiFi.h>

const char* mySSID = "admin";
const char* myPassword = "admin";
const char* targetSSID = "inimodem";
const char* targetPassword = "inimodem";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  
 // Mengatur WiFi ----------------------------------------------------------
  Serial.println();
  Serial.print("Configuring access point...");
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(mySSID, myPassword);
  WiFi.begin(targetSSID, targetPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
  
  Serial.println("");
  Serial.println("WiFi connected");
   
 // Start the server -------------------------------------------------------
  server.begin();
  Serial.println("Server dijalankan");
   
 // Print the IP address ---------------------------------------------------
  Serial.println(WiFi.softAPIP());
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
