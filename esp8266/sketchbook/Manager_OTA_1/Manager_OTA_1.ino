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
  Serial.begin(115200);
  Serial.println("\n Iniciando");
  pinMode(PORTAL_BTN, INPUT_PULLUP);
  pinMode(2,OUTPUT);
  pinMode(16,OUTPUT);
///////////////////////////////////////////////////////////////////
  if ( digitalRead(PORTAL_BTN) == LOW) {//Se botão apertado entra em modo wifi-manager
digitalWrite(2,0);
digitalWrite(16,1);
    //redefinir configurações - para teste
    //wm.resetSettings();
    // definir o tempo limite do portal de configuração
    wm.setConfigPortalTimeout(timeout);
///////////////////////////////////////////////////////////////////
    if (!wm.startConfigPortal("Altava_AP","12345678")) {
      Serial.println("Falha ao conectar e atingiu o tempo limite");
      delay(3000);
      //reinicie e tente novamente, ou talvez coloque-o em sono profundo
      ESP.restart();
      delay(5000);
    }
    //se você chegar aqui, você se conectou ao WiFi
///////////////////////////////////////////////////////////////////
    Serial.println("connectado... :)");
    ArduinoOTA.begin();//ota
  }
}
///////////////////////////////////////////////////////////////////
void loop() {
  // o portal de configuração é solicitado?
    ArduinoOTA.handle();//ota
    ///////////////////////////////////////////////////////////////////
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println(WiFi.localIP());
digitalWrite(2,1);
digitalWrite(16,0);
  } else {
    Serial.println("Não conectou");
    delay(10);
digitalWrite(2,1);
digitalWrite(16,1);
  }
  
///////////////////////////////////////////////////////////////////
  // coloque seu código principal aqui, para executar repetidamente:
}
