#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED1 LED_BUILTIN
#define LED2 16

const char* ssid = "101 residance_fm";       // Nama SSID AP/Hotspot
const char* password = "101littleangel";       // Password Wifi

ESP8266WebServer server(80);      //Menyatakan Webserver pada port 80
String webpage;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

// Connect to WiFi network ------------------------------------------------
  Serial.println();
  Serial.print("Configuring access point...");

// Mengatur WiFi ----------------------------------------------------------
  WiFi.mode(WIFI_AP);                      // Mode Station
  WiFi.begin(ssid, password);               // Mencocokan SSID dan Password
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Print status Connect --------------------------------------------------- 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// Isi dari Webpage -------------------------------------------------------
  webpage+= "<h1> Web Control ESP8266</h1>";
  webpage+= "<p>LED 1 : ";
  webpage+= "<a href=\"LED1ON\"\"><button>ON</button></a><a href=\"LED1OFF\"\"><button>OFF</button></a></p><br>";
  webpage+= "<p>LED 2 : ";
  webpage+= "<a href=\"LED2ON\"\"><button>ON</button></a><a href=\"LED2OFF\"\"><button>OFF</button></a></p><br>";

// Membuat tampilan Webpage -----------------------------------------------
  server.on("/", []() {
    server.send(200, "text/html", webpage);
   });

// Bagian ini untuk merespon perintah yang masuk --------------------------
  server.on("/LED1ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1,LOW);
    delay(1000);
  });
  server.on("/LED2ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2,LOW);
    delay(1000);
  });

  server.on("/LED1OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED1,HIGH);
    delay(1000);
  });
  server.on("/LED2OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(LED2,HIGH);
    delay(1000);
  });
  
  server.begin();
  Serial.println("Webserver dijalankan");
}

void loop() {
   server.handleClient();
}
