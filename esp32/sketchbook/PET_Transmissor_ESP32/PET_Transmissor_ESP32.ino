// ESP 8266 2 Board MAC Address:  A0:20:A6:1A:4B:01
// ESP 8266 3 Board MAC Address:  5C:CF:7F:EE:B1:06
// ESP 32 Board MAC Address:  24:0A:C4:31:93:20
/*** ESP-NOW: TRANSMISSOR Broadcast com ESP-Now*/
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
// ESP8266 endereço Mac (primeiro par)
uint8_t mac_peer1[] = {0xA0, 0x20, 0xA6, 0x1A, 0x4B, 0x01};
// ESP8266 endereço Mac (segundo par)
uint8_t mac_peer2[] = {0x5C, 0xCF, 0x7F, 0xEE, 0xB1, 0x06};
esp_now_peer_info_t peer1;
esp_now_peer_info_t peer2;
int i = 0;
typedef struct message {
  int red;
  int green;
  int blue;
};
struct message myMessage;
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.print("Endereço MAC: ");
  Serial.print(WiFi.macAddress());
  Serial.println("ESP32 ESP-Now Broadcast");
  // Inicializando o ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problema durante a inicialização ESP-NOW");
    return;
  }
  // Registre os pares
  memcpy(peer1.peer_addr, mac_peer1, 6);
  Serial.println("Registrando um par 1");
  if ( esp_now_add_peer(&peer1) == ESP_OK) {
    Serial.println("Peer 1 adicionado");
  }
  memcpy(peer2.peer_addr, mac_peer2, 6);
  Serial.println("Registrando um par 2");
  if ( esp_now_add_peer(&peer2) == ESP_OK) {
    Serial.println("Peer 2 adicionado");
  }
}
void loop() {
  myMessage.red = random(0, 254);
  myMessage.green = random(0, 254);
  myMessage.blue = random(0, 254);
  Serial.println("Envie uma nova mensagem");
  esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));
  delay(1000);
}
