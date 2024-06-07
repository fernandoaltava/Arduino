// ESP 8266 2 Board MAC Address:  A0:20:A6:1A:4B:01
// ESP 8266 3 Board MAC Address:  5C:CF:7F:EE:B1:06
// ESP 8266 sem nome Endereço MAC:80:7D:3A:3E:54:D7
// ESP 8266 tvs      Endereço MAC:80:7D:3A:3E:55:0D
// ESP 32 Board MAC Address:  24:0A:C4:31:93:20
//esp01 80:7D:3A:3E:55:0D
/*** ESP-NOW: RECEPTOR com ESP-Now*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#define led 2
#define buzzer 0
int b = 0;
/////////////////////////////////////////////////////
typedef struct message {
  int red;
  int green;
  int blue;
} message;
message myMessage;
/////////////////////////////////////////////////////
void onDataReceiver(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  Serial.println("Message received.");
  // Não usamos o mac para verificar o remetente
  // Vamos transformar os dados de entrada em nossa estrutura de mensagem
  memcpy(&myMessage, incomingData, sizeof(myMessage));
  Serial.print("Red:");
  Serial.println(myMessage.red);
  Serial.print("Green:");
  Serial.println(myMessage.green);
  Serial.print("Blue:");
  Serial.println(myMessage.blue);
  if (myMessage.blue > 0) {
    digitalWrite(led, !digitalRead(led));
    b = b + 1;
  }
}
/////////////////////////////////////////////////////
void toca() {
  //for (int a = 0; a < 11; a++) {
    tone(buzzer, 7800); // Send 1KHz sound signal...
    delay(100);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(50);        // ...for 1sec
  //}
}
/////////////////////////////////////////////////////
void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  WiFi.disconnect();
  ESP.eraseConfig();
  WiFi.mode(WIFI_STA);
  Serial.println(" ");
  Serial.print("Endereço MAC:");
  Serial.print(WiFi.macAddress());
  Serial.println("\nReceptor ESP-Now");
  //delay(10000);
  //   Inicializando o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problema durante a inicialização ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(onDataReceiver);
}
/////////////////////////////////////////////////////
void loop() {
  if (b > 0) toca();
  b = 0;
}
