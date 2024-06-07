#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando...");
    WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP", "40224022");

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.setHostname("Garagem");
  ArduinoOTA.setPassword("4022");
  ArduinoOTA.begin();
}
void loop() {
  ArduinoOTA.handle();
}
