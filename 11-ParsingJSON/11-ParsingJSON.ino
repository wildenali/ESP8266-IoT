#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Parameters
const char* ssid = "inimodem";
const char* password = "inimodem";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://jsonplaceholder.typicode.com/users/1");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Parsing
      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      // Parameters
      int id = root["id"];                      // 1
      const char* name = root["name"];          // "Leanne Graham"
      const char* username = root["username"];  // "Bret"
      const char* email = root["email"];        // "Sincere@april.biz"
      const char* addrStreet = root["address"]["street"];    // Object Address, isinya banyak
      const char* addrSuite = root["address"]["suite"];
      const char* addrCity = root["address"]["city"];
      const char* addrZipcode = root["address"]["zipcode"];
      const char* addrGeoLat = root["address"]["geo"]["lat"];
      const char* addrGeoLng = root["address"]["geo"]["lng"];
      const char* phone = root["phone"];        // "1-770-736-8031 x56442"
      const char* website = root["website"];    // hildegard.org
      const char* compName = root["company"]["name"];    // Objek
      const char* compCatchPhrase = root["company"]["catchPhrase"];
      const char* compBs = root["company"]["bs"];
      
      // Output to serial monitor
      Serial.print("Name      : ");
      Serial.println(name);
      Serial.print("Username  : ");
      Serial.println(username);
      Serial.print("Email     : "); 
      Serial.println(email);
      Serial.println("Address");
        Serial.print("   Street   : "); 
        Serial.println(addrStreet);
        Serial.print("   Suite    : "); 
        Serial.println(addrSuite);
        Serial.print("   City     : "); 
        Serial.println(addrCity);
        Serial.print("   Zipcode  : "); 
        Serial.println(addrZipcode);
        Serial.print("   Lat      : "); 
        Serial.println(addrGeoLat);
        Serial.print("   Lng      : "); 
        Serial.println(addrGeoLng);
      Serial.print("Phone     : "); 
      Serial.println(phone);
      Serial.print("Website   : "); 
      Serial.println(website);
      Serial.println("Company"); 
        Serial.print("   Name         :"); 
        Serial.println(compName);
        Serial.print("   Catch Phrase :");
        Serial.println(compCatchPhrase);
        Serial.print("   bs           :"); 
        Serial.println(compBs);
      Serial.println("-----------------------------------------");
    }
    http.end();   //Close connection
  }
  // Delay
  delay(5000);
}
