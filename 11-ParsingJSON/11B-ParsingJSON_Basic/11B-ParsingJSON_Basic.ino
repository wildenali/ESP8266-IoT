#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  Serial.println();  //Clear some garbage that may be printed to the serial console
}

void loop() {

  Serial.println("——————");
 
  char JSONMessage[] = " {\"SensorType\": \"Temperature\", \"Value\": 10}"; //Original message
  Serial.print("Initial string value: ");
  Serial.println(JSONMessage);
 
  StaticJsonBuffer<300> JSONBuffer;   //Memory pool
  JsonObject& parsed = JSONBuffer.parseObject(JSONMessage); //Parse message
 
  if (!parsed.success()) {   //Check for errors in parsing
    Serial.println("Parsing failed");
    delay(5000);
    return;
  }
 
  const char * sensorType = parsed["SensorType"]; //Get sensor type value
  int value = parsed["Value"];                                         //Get value of sensor measurement
 
  Serial.println(sensorType);
  Serial.println(value);
 
  Serial.print("Final string value: ");
 
  for (int i = 0; i < 31; i++) { //Print the modified string, after parsing
    Serial.print(JSONMessage[i]);
  }
 
  Serial.println();
  delay(5000);
}
