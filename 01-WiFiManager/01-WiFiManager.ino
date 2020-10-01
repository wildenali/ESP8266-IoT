#include "pairing.h"

void setup() {
  Serial.begin(115200);
  
  pairingSetup();
  Serial.println("go to loop .............................................");
}

void loop() {
  pairingCheckWiFi();
  pairingCheckButton();
}
