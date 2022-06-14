#include <Arduino.h>
#include <painlessMesh.h>

// some gpio pin that is connected to an LED...
// on my rig, this is 5, change to the right number of your LED.
#define   LED             2       // GPIO number of connected LED, ON ESP-12 IS GPIO2

#define   BLINK_PERIOD    3000 // milliseconds until cycle repeat
#define   BLINK_DURATION  100  // milliseconds LED is on for

#define   MESH_SSID       "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555
int gateVal=0;
int check=1;
int timer=0;
// Prototypes
void sendMessage(); 
void receivedCallback(uint32_t from, String & msg);
void newConnectionCallback(uint32_t nodeId);
void changedConnectionCallback(); 
void nodeTimeAdjustedCallback(int32_t offset); 
void delayReceivedCallback(uint32_t from, int32_t delay);

Scheduler     userScheduler;
 // to control your personal task
painlessMesh  mesh;

void sendMessage() ;
void handleUART(); // Prototype
Task taskSendMessage( TASK_SECOND * 1, TASK_FOREVER, &sendMessage );
//Task taskHandleUART( TASK_SECOND * 1, TASK_FOREVER, &handleUART );  // start with a one second interval

// Task to blink the number of nodes

// 1 for val 
// 2 for HELP 
// 3 for q
// 4 for not q
void sendToGUI(int i,uint32_t from){
 // if(Serial.available()){
      Serial.print("G");
      Serial.print(from);
      Serial.print("#");
      switch (i)
      {
      case 1:
        Serial.println(gateVal);
        break;
      case 2:
        Serial.println("HELP");
        break;
      case 3:
        Serial.println("Q");
        break;
      case 4:
        Serial.println("N");
        break;
      default:
        break;
      }
 // }
}
void setup() {
  Serial.begin(115200);



  mesh.setDebugMsgTypes(ERROR | DEBUG);  // set before init() so that you can see error messages

  mesh.init(MESH_SSID, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  mesh.onNodeDelayReceived(&delayReceivedCallback);

  userScheduler.addTask( taskSendMessage );
  //userScheduler.addTask(taskHandleUART);
  taskSendMessage.enable();
  //taskHandleUART.enable();



}

void loop() {
  mesh.update();
}

void sendMessage() {

 DynamicJsonDocument jsonBuffer(1024);
JsonObject msg = jsonBuffer.to<JsonObject>();
  msg["type"]=5;
    String str;
  serializeJson(msg, str);

  mesh.sendBroadcast(str);
  taskSendMessage.delay(200000);
  taskSendMessage.delau
}


void receivedCallback(uint32_t from, String & msg) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());\
    DynamicJsonDocument doc(1024);
  deserializeJson(doc, msg);
  int type=doc["type"];
  int data=doc["data"];
  switch(type)
  {
    case 1:
    {
      gateVal=data;
      sendToGUI(1,from);
      break;
    }
    case 2:
    {
      if(data)
      {

        sendToGUI(3,from);

      }
      else
      {

        sendToGUI(4,from);
      }
      break;
    }
    case 3:
    {
       sendToGUI(2,from); //HELP
    }

    default:
    {
      
      break;
    }
  }
}

void newConnectionCallback(uint32_t nodeId) {
  // Reset blink task

}

void changedConnectionCallback() {
  //Serial.printf("Changed connections\n");
  // Reset blink task

  //nodes = mesh.getNodeList();

  //Serial.printf("Num nodes: %d\n", nodes.size());
  //Serial.printf("Connection list:");

  //SimpleList<uint32_t>::iterator node = nodes.begin();
  
}

void nodeTimeAdjustedCallback(int32_t offset) {
 // Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void delayReceivedCallback(uint32_t from, int32_t delay) {
  //Serial.printf("Delay to node %u is %d us\n", from, delay);
}