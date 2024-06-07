#if defined(ESP32)
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;

#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

const uint32_t TempoEsperaWifi = 5000;

void setup() {
  WiFi.persistent(false);
  delay(100);
  WiFi.persistent(true);
  delay(100);
  WiFi.persistent(false);
  delay(100);
  Serial.begin(115200);         // Inicie a comunicação serial para enviar mensagens para o computador
  Serial.println("\nIniciando multi Wifi");

  wifiMulti.addAP("Luana2", "40224022");   // aadicione as redes Wi-Fi às quais deseja se conectar
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  WiFi.mode(WIFI_STA);
  wifiMulti.run();
  Serial.println("Conectando...");
  while (wifiMulti.run(TempoEsperaWifi) != WL_CONNECTED) { // Aguarde a conexão do Wi-Fi: procure redes Wi-Fi e conecte-se à mais forte das redes acima
    delay(100);
    Serial.print('.');
  }
  Serial.print("Conectado a:  ");
  Serial.println(WiFi.SSID());              // Diga-nos a qual rede estamos conectados
  Serial.print("IP:\t");
  Serial.println(WiFi.localIP());           // Envie o endereço IP do ESP8266 para o computador
}
void loop() {
  AtualizarWifi();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Com Wifi");
  } else {
    Serial.println("Sem Wifi");
  }
  delay(1000);
}
void AtualizarWifi() {
  if (wifiMulti.run(TempoEsperaWifi) != WL_CONNECTED) {
    Serial.println("Não conectado a Wifi");
  }
}
