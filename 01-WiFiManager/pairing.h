/**
 * WiFiManager advanced demo, contains advanced configurartion options
 * Implements TRIGGEN_PIN button press, press for ondemand configportal, hold for 3 seconds for reset settings.
 */
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <Ticker.h> //for LED status

WiFiManager wm; // global wm instance
Ticker tickerLedStatus;  //for LED status

#define pairingPin D2

bool cariWiFi = true;

void tickLedStatus()
{
  int state = digitalRead(LED_BUILTIN);  // get the current state of led pin
  digitalWrite(LED_BUILTIN, !state);     // set pin to the opposite state
}

void pairingCheckButton(){
  // check for button press
  if ( digitalRead(pairingPin) == LOW ) {
    delay(50);
    if( digitalRead(pairingPin) == LOW ){
      Serial.println("Button Pressed");
      tickerLedStatus.attach(0.1, tickLedStatus);
      delay(3000); // reset delay hold
      if( digitalRead(pairingPin) == LOW ){
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();
        delay(2000);
        ESP.restart();
      }
    }
  }
}

void pairingCheckWiFi() {
  if(WiFi.status() != WL_CONNECTED && cariWiFi == true) {
    Serial.println("Cari WiFi");
    tickerLedStatus.attach(1.0, tickLedStatus);
    cariWiFi = false;
  } else if(WiFi.status() == WL_CONNECTED && cariWiFi == false){
    Serial.println("Akhirnya Konek");
    tickerLedStatus.detach();
    digitalWrite(LED_BUILTIN, LOW); //keep LED on
    cariWiFi = true;
  }
}


String getParam(String name){
  //read parameter from server, for customhmtl input
  String value;
  if(wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback(){
  Serial.println("[CALLBACK] saveParamCallback fired");
  Serial.println("PARAM customfieldid = " + getParam("customfieldid"));
}

void pairingSetup() {
  //Set GPIO
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pairingPin, INPUT_PULLUP);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  
  Serial.setDebugOutput(true);  
  delay(1000);
  
  wm.setSaveParamsCallback(saveParamCallback);

  std::vector<const char *> menu = {"wifi","info","restart","exit"};
  wm.setMenu(menu);

  // set dark theme
  wm.setClass("invert");

  //set static ip
  // wm.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0)); // set static ip,gw,sn
  // wm.setShowStaticFields(true); // force show static ip fields
  // wm.setShowDnsFields(true);    // force show dns field always

  wm.setConfigPortalTimeout(30); // auto close configportal after n seconds

  bool res;
  res = wm.autoConnect("wilden board"); // password protected ap

  if(!res) {
    Serial.println("Failed to connect or hit timeout");
  } 
  else {
    Serial.println("connected...SETUP...yeey :)");
    cariWiFi = false;
  }
}
