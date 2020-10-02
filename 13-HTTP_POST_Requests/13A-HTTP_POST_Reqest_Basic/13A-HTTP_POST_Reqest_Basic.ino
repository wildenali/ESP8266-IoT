#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "inimodem";
const char* password = "inimodem";

void setup () {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..");
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    HTTPClient http;    //Declare object of class HTTPClient
    http.begin("http://192.168.1.88:8085/hello");      //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header

    int httpCode = http.POST("Message from ESP8266");   //Send the request
    String payload = http.getString();                  //Get the response payload

    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload

    http.end();  //Close connection
  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(5000);  //Send a request every 30 seconds

}
