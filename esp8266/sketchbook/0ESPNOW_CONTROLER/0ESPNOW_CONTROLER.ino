#include <ESP8266WiFi.h>
#include <espnow.h>
uint8_t remoteMac[] = { 0x40, 0xF5, 0x20, 0x06, 0x26, 0xDB };
const int buttonPin = 5;
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_now_init();
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteMac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    uint8_t dataToSend = 1;
    Serial.print("Data Sent:");
    Serial.println(dataToSend);
    esp_now_send(remoteMac, &dataToSend, sizeof(dataToSend));
    delay(10);
  } else {
    uint8_t dataToSend = 0;
    Serial.print("Data Sent:");
    Serial.println(dataToSend);
    esp_now_send(remoteMac, &dataToSend, sizeof(dataToSend));
    delay(10);
  }
}
//////////////////////////////////////////
/*Substitua a variável remoteMAC pelo endereço MAC do seu receptor ESP8266.

Código explicado:
O código primeiro inclui as bibliotecas ESP8266WiFi.he espnow.h. 
Essas bibliotecas são necessárias para que o ESP8266 se comunique usando o ESP-NOW.
A próxima linha define o endereço MAC do dispositivo remoto. Este é o dispositivo para o qual o ESP8266 enviará os dados.
A const int buttonPin = D5;linha define o pino ao qual o botão está conectado. 
Neste caso, o botão está conectado ao pino D5 do GPIO.
A setup()função inicializa a porta serial, define o pino do botão como entrada e configura o ESP8266 para usar o ESP-NOW. 
Ele também define o ESP8266 como controlador e adiciona o dispositivo remoto como par.
A loop()função verifica continuamente o estado do botão. 
Se o botão for pressionado, o ESP8266 envia um pacote de dados para o dispositivo remoto. 
O pacote de dados contém um único byte, que pode ser 0 ou 1, dependendo de o botão ser pressionado ou não.
A esp_now_send()função envia o pacote de dados para o dispositivo remoto. 
O primeiro parâmetro é o endereço MAC do dispositivo remoto, 
o segundo parâmetro é um ponteiro para o buffer de dados e o terceiro parâmetro é o tamanho do buffer de dados.
A delay()função pausa a execução do código por um número especificado de milissegundos.
Em resumo, o código usa ESP-NOW para enviar um pacote de dados a um dispositivo remoto sempre que o botão é pressionado. 
O pacote de dados contém um único byte, que pode ser 0 ou 1, dependendo de o botão ser pressionado ou não.
*/
