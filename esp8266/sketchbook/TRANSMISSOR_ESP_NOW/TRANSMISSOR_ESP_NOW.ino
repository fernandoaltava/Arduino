// ESP 8266 2 Board MAC Address:  A0:20:A6:1A:4B:01
// ESP 8266 3 Board MAC Address:  5C:CF:7F:EE:B1:06
// ESP 32 Board MAC Address:  24:0A:C4:31:93:20
/**
* ESP-NOW esp8266
*
* Transmissor
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <SPI.h>
#include <Wire.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPin D6
int soma=0; 
uint8_t peer1[] = {0x24, 0x0A, 0xC4, 0x31, 0x93, 0x20};
 
typedef struct message {
  float temperature;
  float humidity;
  int conta;
};
struct message myMessage;
 
// Inicializa o sensor DHT.
DHT dht(DHTPin, DHTTYPE);
 
void onSent(uint8_t *mac_addr, uint8_t sendStatus) {
 Serial.println("Status:");
 Serial.println(sendStatus);
}
 
void setup() {
 Serial.begin(115200);
 dht.begin();
 WiFi.mode(WIFI_STA);
 // Obter Mac Add
 Serial.print("Endereço MAC:");
 Serial.print(WiFi.macAddress());
 Serial.println("ESP-Now Sender");
 // Inicializando o ESP-NOW
 if (esp_now_init() != 0) {
   Serial.println("Problema durante a inicialização ESP-NOW");
   return;
 }
 esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
 // Registre o par
 Serial.println("Registrando um par");
 esp_now_add_peer(peer1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
 Serial.println("Registrando a função de retorno de chamada");
 esp_now_register_send_cb(onSent);
}
 
void loop() {
  soma=soma+1;
 myMessage.temperature = dht.readTemperature();
 myMessage.humidity = dht.readHumidity();
 myMessage.conta=soma;
 
 Serial.println("Envie uma nova mensagem");
 esp_now_send(NULL, (uint8_t *) &myMessage, sizeof(myMessage));
 
 delay(500);
}
