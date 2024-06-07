#include "outra.h"
#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WebServer.h>     ///https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <DNSServer.h>
char char_server_emoncms[40]="serveremoncms.com";
char char_port_emoncms[4] = "80";
char char_apikey_emoncms[33] = "****************************";
char char_updatedata_emoncms[4] = "60";
char char_input_emoncms[20] = "variable_name";
char char_node_emoncms[4] = "1";
const char* host;
int port; 
const char* apikey;
int updatedata; 
const char* inputname;
int nodedata;
const char* ssid_apmode = "ESP_emoncms";
//flag for saving data
bool shouldSaveConfig = false;
bool initialConfig = false;
bool parameterOK = false;
//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
void x1();
void x2();
void x3();

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
