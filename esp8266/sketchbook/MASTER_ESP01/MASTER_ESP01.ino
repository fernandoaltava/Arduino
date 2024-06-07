//=================================================================================================//
// MASTER                                                                                          //
#include <ESP8266WiFi.h>
extern "C" {
#include <espnow.h>
}
// This is the slave MAC Address which receives the data
 uint8_t mac[] = {0x5C, 0xCF, 0x7F, 0x4C, 0x82, 0x5C}; //AP MAC SLAVE'S ADDRESS

  #define WIFI_CHANNEL 4
  int prevstate_1 = LOW;
  int prevstate_2 = LOW;

// Data structure, must be the same for the slave

struct __attribute__((packed))DataStruct {
  char text[32];
};
    DataStruct button_1;
    DataStruct button_2;

//=====================================================================================================
void setup() {
////  pinMode(D1, INPUT_PULLUP);
////  pinMode(D4, INPUT_PULLUP);
////  pinMode(D2, OUTPUT);
////  pinMode(D3, OUTPUT);

//  Serial.begin(115200); Serial.println();
//  Serial.println("Starting EspnowController.ino");
  WiFi.mode(WIFI_STA); // Station mode for esp-now controller
  WiFi.disconnect();
//  Serial.printf("This mac: %s, ", WiFi.macAddress().c_str());
//  Serial.printf("slave mac: %02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
//  Serial.printf(", channel: %i\n", WIFI_CHANNEL);
  if (esp_now_init() != 0)
  {
//    Serial.println("*** ESP_Now initialization failed");
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(mac, ESP_NOW_ROLE_SLAVE, WIFI_CHANNEL, NULL, 0);
  strcpy(button_1.text, "Button 01 pressed");
  strcpy(button_2.text, "Button 02 pressed");
//  Serial.println("Setup finished");
}

//======================================================================================================

void loop() {
  sendData();
}

//======================================================================================================
void sendData() {

////  int currentstate_1 = digitalRead(D4);
////  if (prevstate_1 != currentstate_1) {
////    if (currentstate_1 == LOW) {
      uint8_t bs[sizeof(button_1)];
      memcpy(bs, &button_1, sizeof(button_1));
      esp_now_send(mac, bs, sizeof(button_1));
//      Serial.println(button_1.text);
////      digitalWrite(D2, !digitalRead(D2));
////    }
////  } prevstate_1 = currentstate_1;
delay(100);
}

//========================================== www.fvml.com.br ===========================================
