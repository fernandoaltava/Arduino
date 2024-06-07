#include <ESP8266WiFi.h>//ota
#include <ArduinoOTA.h> //ota
#include <ESP8266mDNS.h>//ota
#include <WiFiManager.h>//manager
#define PORTAL_BTN 5    //manager
int timeout = 120;      //manager
WiFiManager wm;         //manager
///////////////////////////////////////////////////////////////////
void setup() {
  WiFi.mode(WIFI_STA); // modo definido explicitamente, o padrão esp é STA+AP
  ///////////////////////////////////////////////////////////////////
  // coloque seu código de configuração aqui, para executar uma vez:
  Serial.begin(9600);
  Serial.println("\n Iniciando");
  bool res;
  pinMode(PORTAL_BTN, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(16, OUTPUT);
  ///////////////////////////////////////////////////////////////////
  while (digitalRead(PORTAL_BTN) == LOW) { //Se botão apertado entra em modo wifi-manager
    digitalWrite(2, 0);
    digitalWrite(16, 1);
    wm.resetSettings();
    wm.setConfigPortalTimeout(timeout);
    delay(2000);
  }
  ///////////////////////////////////////////////////////////////////
  res = wm.autoConnect("Altava_AP", "12345678");
  if (!res) {
    Serial.println("Falha na conexão");
    ESP.restart();
  }
  else {
    Serial.println("Conectado :)");
    wm.stopConfigPortal();
  }
  ///////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////
void loop() {
  ArduinoOTA.handle();//ota
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.hostname());
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());
    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.subnetMask());
    digitalWrite(2, 1);
    digitalWrite(16, 0);
    ArduinoOTA.begin();//ota
  } else {
    Serial.println("Não conectou");
    delay(10);
    ESP.restart();
    digitalWrite(2, 1);
    digitalWrite(16, 1);
  }
  delay(1000);
  ///////////////////////////////////////////////////////////////////
  // coloque seu código principal aqui, para executar repetidamente:
}
