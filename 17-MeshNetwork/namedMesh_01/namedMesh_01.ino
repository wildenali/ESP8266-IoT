//************************************************************
// this is a simple example that uses the painlessMesh library
// 
// This example shows how to build a mesh with named nodes
//
//************************************************************
#include "namedMesh.h"
#include "tombol.h"

#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

Scheduler     userScheduler; // to control your personal task
namedMesh  mesh;

String nodeName = "sensor_1"; // Name needs to be unique

Button tombolKu(D1);

//Task taskSendMessage( TASK_SECOND*1, TASK_FOREVER, []() {
//    String msg = String("This is a message from: ") + nodeName + String(" for logNode");
//    String to = "sensor_2";
//    mesh.sendSingle(to, msg); 
//}); // start with a one second interval

void setup() {
  Serial.begin(115200);
  tombolKu.begin();

  mesh.setDebugMsgTypes(ERROR | DEBUG | CONNECTION);  // set before init() so that you can see startup messages

  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);

  mesh.setName(nodeName); // This needs to be an unique name! 

//  mesh.onReceive([](uint32_t from, String &msg) {
//    Serial.printf("Received message by id from: %u, %s\n", from, msg.c_str());
//  });

  mesh.onReceive([](String &from, String &msg) {
    Serial.printf("Terima pesan dari: %s, berisi: %s\n", from.c_str(), msg.c_str());
  });

  mesh.onChangedConnections([]() {
    Serial.printf("Changed connection\n");
  });

//  userScheduler.addTask(taskSendMessage);
//  taskSendMessage.enable();
  pinMode(D1, INPUT_PULLUP);
}

void loop() {
  // it will run the user scheduler as well
//  if(digitalRead(D1) == LOW){
//    String msg = String("This is a message from: ") + nodeName + String(" for logNode");
//    String to = "sensor_2";
//    mesh.sendSingle(to, msg);
//  }

  if (tombolKu.isReleased()) {
//    Serial.println(F("Released"));
    String msg = String("A1");
    String to = "sensor_2";
    mesh.sendSingle(to, msg);
    Serial.println("Kirim pesan ke: " + to + " berisi: " + msg);
  }
        
  mesh.update();
}
