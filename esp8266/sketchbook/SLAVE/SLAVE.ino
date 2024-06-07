//==========================================================================================//
// SLAVE                                                                                    //
#include <ESP8266WiFi.h>
extern "C" {
#include <espnow.h>
#include <user_interface.h>
}
 uint8_t mac[] = {0x5C, 0xCF, 0x7F, 0x4C, 0x82, 0x5C}; //AP MAC SLAVE'S ADDRESS

//============================================================================================

int Led1 = D0;
int Led2 = D1;
  
void initVariant() {
  WiFi.mode(WIFI_AP);
  wifi_set_macaddr(SOFTAP_IF, &mac[0]);
}

//=============================================================================================
#define WIFI_CHANNEL 4

// must match the controller struct
struct __attribute__((packed))DataStruct { 
  char text[32];
  unsigned int time;};

DataStruct receivedData;

//=============================================================================================
void setup() {
//  Serial.begin(115200); Serial.println();
//  Serial.println("Starting EspnowSlave.ino");
//  Serial.print("This node AP mac: "); Serial.println(WiFi.softAPmacAddress());
//  Serial.print("This node STA mac: "); Serial.println(WiFi.macAddress());
  pinMode(Led1,OUTPUT);
  pinMode(Led2,OUTPUT);

  if (esp_now_init() != 0) {
//    Serial.println("*** ESP_Now init failed");
    while (true) {};
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(receiveCallBackFunction);
//  Serial.println("End of setup - waiting for messages");
}

//==============================================================================================

void loop() {
}

//==============================================================================================
void receiveCallBackFunction(uint8_t *senderMac, uint8_t *incomingData, uint8_t len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));

  String DataCompare = String(receivedData.text);

  if(DataCompare == "Button 01 pressed"){
  digitalWrite(Led1, !digitalRead(Led1));
//  Serial.println(" Message = " + DataCompare);
 }
  if(DataCompare == "Button 02 pressed"){
  digitalWrite(Led2, !digitalRead(Led2));
//  Serial.println(" Message = " + DataCompare);
   
  }
}

//======================================= www.fvml.com.br ========================================
 
