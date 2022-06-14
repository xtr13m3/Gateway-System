#include "painlessMesh.h"
#include "gateServo.h"
#include "gateDetector.h"
#include "occupCtr.h"
//#include "QueueDetector.h"

#define   MESH_PREFIX     "whateverYouLike"
#define   MESH_PASSWORD   "somethingSneaky"
#define   MESH_PORT       5555

int value=0;
int pcID=0;
int gateVal=0;
int isLead=1;
int t=0;
int dist1=0;
int dist2=0;
int flagQueue=0;
//int occCounter=0;

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

//QueueDetector QD = QueueDetector(TRIG,ECHO,LED);
Gate gate = Gate(PWM_FREQ, PWM_CH,PWM_RES, SERVO);
MovDetector D1 = MovDetector(TRIG_1, ECHO_1, LED_1);
MovDetector D2 = MovDetector(TRIG_2, ECHO_2, LED_2);

// User stub
void idle() ; // Prototype so PlatformIO doesn't complain
void gateHandler();
void sendToGUI();

//the idle task
//Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &idle );
Task taskGate(TASK_SECOND*1,TASK_FOREVER,&gateHandler);
//Task taskSendToGUI(TASK_SECOND*1,TASK_FOREVER,&sendToGUI);

int onGateReceive(){

  String readString;
  while(Serial.available())
  {
    char c = Serial.read();  //gets one byte from serial buffer
      readString += c;
      delay(3);
  }
  if (readString.length() >0) {
    int n = readString.toInt();
    Serial.print("Recieved from nucleo: ");
    Serial.println(n);
    readString="";
      return  n;
  } 
  else return 0;
}
// Broadcast Message to increment the Nr of people
void incrementMeshMessage() {
  DynamicJsonDocument jsonBuffer(1024);
  JsonObject msg = jsonBuffer.to<JsonObject>();
  msg["type"]=1;
  msg["data"]=1;
    String str;
  serializeJson(msg, str);

  mesh.sendBroadcast(str);
}
// Broadcast Message to decrement the Nr of people
void decrementMeshMessage() {
  DynamicJsonDocument jsonBuffer(1024);
  JsonObject msg = jsonBuffer.to<JsonObject>();
  msg["type"]=1;
  msg["data"]=-1;
   String str;
  serializeJson(msg, str);
  mesh.sendBroadcast(str);
}
// Send message to destination server for help
void helpMeMessage()
{
  DynamicJsonDocument jsonBuffer(1024);
  JsonObject msg = jsonBuffer.to<JsonObject>();
  msg["type"]=2;
  msg["data"]=1;
   String str;
  serializeJson(msg, str);
  //mesh.sendSingle(dest,str);
  mesh.sendBroadcast(str);
}
// Broadcast queue state 0 for none 1 for existing queue
void sendQueue(int state)
{
  DynamicJsonDocument jsonBuffer(1024);
  JsonObject msg = jsonBuffer.to<JsonObject>();
  msg["type"]=3;
  msg["data"]=state;
   String str;
  serializeJson(msg, str);
  mesh.sendBroadcast(str);
}

void sendPCVal(){
    if(pcID!=0){
    DynamicJsonDocument jsonBuffer(1024);
  JsonObject msg = jsonBuffer.to<JsonObject>();
  msg["type"]=1;
  msg["data"]=gateVal;
  String str;
  serializeJson(msg, str);
  mesh.sendSingle(pcID,str);
    }
}
void sendPCQueue(int queue){
  if(pcID!=0){
  DynamicJsonDocument jsonBuffer(1024);
  JsonObject msg = jsonBuffer.to<JsonObject>();
  msg["type"]=2;
  msg["data"]=queue;
  String str;
  serializeJson(msg, str);
  mesh.sendSingle(pcID,str);
  }
}
void sendPCHelp(){
  if(pcID!=0){
  DynamicJsonDocument jsonBuffer(1024);
  JsonObject msg = jsonBuffer.to<JsonObject>();
  msg["type"]=3;
  String str;
  serializeJson(msg, str);
  mesh.sendSingle(pcID,str);
  }
}
// Needed for painless library

void occupCounter(void){
  if((dist1 > 0 && dist1 <= 50) && !(dist2 > 0 && dist2 <=50))
  {
    gateVal++;
    value++;
    incrementMeshMessage();
    sendPCVal();
    Serial.println("IN");
    digitalWrite(LED_1, HIGH);
    gate.openGate();
    //delay(2000);

  }
  else if(!(dist1 > 0 && dist1 <= 50) && (dist2 > 0 && dist2 <= 50)){
    gateVal--;
    value--;
    decrementMeshMessage();
    sendPCVal();
    Serial.println("OUT");
    digitalWrite(LED_2, HIGH);
    gate.openGate();
   // delay(2000);
  }
  else
  {
    gate.closeGate();
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
  }
}


void gateHandler(){
 
  dist1 = D1.measureDist();
  dist2 = D2.measureDist();
  occupCounter();
 
 //taskGate.delay(100);
}

 void idle()
{
  int handle=onGateReceive();
  switch(handle)
  {
    case 1:
    {
      incrementMeshMessage();
      Serial.println("Incrementing");
      value ++;
      gateVal++;
      sendPCVal();
      break;
    }
    case 2:
    {
      decrementMeshMessage();
      Serial.println("Decrementing");
      value--;
      gateVal--;
      sendPCVal();
      break;
    }
    case 3:
    {
      Serial.println("Help required at:");
      helpMeMessage();
      sendPCHelp();
      break;
    }
    case 4:
    {
      Serial.println("Queue");
      sendQueue(1);
      sendPCQueue(1);
      break;
    }
    case 5:
    {
      Serial.println("No Queue");
      sendQueue(0);
      sendPCQueue(0);

      break;
    }
    default:
    {
      break;
    }
  }
}
void receivedCallback( uint32_t from, String &msg )
{
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, msg);
  int type=doc["type"];
  int data=doc["data"];
  switch(type)
  {
    case 1:
    {
      value = value + data;
      Serial.print("Value: ");
      Serial.print(value);
      Serial.println();
      break;
    }
    case 2:
    {
      Serial.print("Help needed at: ");
      Serial.println(from);

      break;
    }
    case 3:
    {
      if(data)
      {
        Serial.print("Queue on gate ");
        Serial.println(from);

      }
      else
      {
        Serial.print("No queue on gate ");

      }
      break;
    }
    case 4:
    {

      break;
    }
    case 5:
    {
      pcID=from;
      sendPCVal();
      break;
    }
    default:
    {
      Serial.println("Wrong type");
      break;
    }
  }
}

void newConnectionCallback(uint32_t nodeId) {

    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
    // if the node is the first in the network any other nodes connected after are sent the database and notice of the lead


}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(9600);
 // Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  
  //mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
 // userScheduler.addTask( taskSendMessage );
  userScheduler.addTask(taskGate);
  //userScheduler.addTask(taskSendToGUI);
  //taskSendMessage.enable();
  taskGate.enable();
  //taskDbRefresh.enable();
  
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();

}
