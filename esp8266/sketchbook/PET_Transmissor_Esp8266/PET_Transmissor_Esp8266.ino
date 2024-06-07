// ESP 8266 2 Board MAC Address:  A0:20:A6:1A:4B:01
// ESP 8266 3 Board MAC Address:  5C:CF:7F:EE:B1:06
// ESP 8266 sem nome Endereço MAC:80:7D:3A:3E:54:D7
// ESP 8266 tvs      Endereço MAC:80:7D:3A:3E:55:0D
// ESP 32 Board MAC Address:  24:0A:C4:31:93:20
//esp01 80:7D:3A:3E:55:0D
/*** ESP-NOW: TRANSMISSOR Broadcast com ESP-Now*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
// ESP8266 endereço Mac (primeiro par)
uint8_t mac_peer1[] = {0x80, 0x7D, 0x3A, 0x3E, 0x54, 0xD7};
// ESP8266 endereço Mac (segundo par)
uint8_t mac_peer2[] = {0x80, 0x7D, 0x3A, 0x3E, 0x55, 0x0D};
//uint8_t mac_peer2[] = {0x80, 0x7D, 0x3A, 0x3E, 0x55, 0x0D};
#define led 2

////////////////////////////////////////////////
typedef struct message {
  int red;
  int green;
  int blue;
};
struct message myMessage;
////////////////////////////////////////////////
void onSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Status: ");
  Serial.println(sendStatus);
}
////////////////////////////////////////////////
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  ESP.eraseConfig();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("ESP-Now enviar ");
  // Iniciando o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problema na iniciação ESP-NOW ");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  Serial.println("Registrando o par 1 ");
  esp_now_add_peer(mac_peer1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  Serial.println("Registrando o par 2 ");
  esp_now_add_peer(mac_peer2, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  Serial.println("Registrando a função enviar callback ");
  esp_now_register_send_cb(onSent);
}
////////////////////////////////////////////////
void loop() {
  digitalWrite(led, !digitalRead(led));
  myMessage.red = random(0, 254);;
  myMessage.green = random(0, 254);;
  myMessage.blue = random(0, 254);;
  Serial.println("Enviar nova mensagem ");
  Serial.print("Vermelho: ");
  Serial.println(myMessage.red);
  Serial.print("Verde:    ");
  Serial.println(myMessage.green);
  Serial.print("Azul:     ");
  Serial.println(myMessage.blue);
  Serial.println(WiFi.macAddress());
  esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));
  delay(100);
}
