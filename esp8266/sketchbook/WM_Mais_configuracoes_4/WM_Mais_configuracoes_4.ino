#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>     ///https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "Manager.h"
#include "Firebase.h"

char SENHA[] = "4022";
char CHAVE[] = "Switch9";//mude a chave apenas aqui

#define button_config  5  ///PIN D1 NodeMCU  /// Normalmente Aberto // 
#define pin_led_Wifi  14 //led verde  
#define pin_led_App   4  //led vermelho 

String b = " ";
int a = 0;
void mont_FS();
void tela1();
void tela2();
void leChave(String chave, int porta);
void escreveIntFireBase(String chave, int valor);
void escreveStringFireBase(String chave, String valor);
void leSlider1();
void leSlider2();
void leSlider3();

void setup() {
  // coloque seu código de configuração aqui, para executar uma vez:
  Serial.begin(115200);
  Serial.println("\n Starting");
  pinMode(button_config, INPUT_PULLUP);
  pinMode(pin_led_Wifi, OUTPUT);
  pinMode(pin_led_App, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(2, OUTPUT);

  Serial.println("Montagem FS...");
  mont_FS();
  if ( digitalRead(button_config) == HIGH ) {
    digitalWrite(pin_led_Wifi, HIGH);
    tela1();
  }
  tela2();

  ArduinoOTA.setHostname(CHAVE);
  ArduinoOTA.setPassword(SENHA);
  ArduinoOTA.begin();
  ////////////////////////////////////////////////////////////////
  delay(500);
  //  ESP.wdtDisable();//desabilita wdt por software habilita wdt por hardware de 8 segundos
  digitalWrite(16, 1);
  digitalWrite(2, 1);
  ////////////////////////////////////////////////////////////////
  //  Firebase.begin("https://controle-geral-a6bb8.firebaseio.com", "Qk1YiNYmcD5dTlmOe8gXzMLQaadybQXPnUp5Lsqc");
  Firebase.begin("https://" + String(char_server_emoncms), "Qk1YiNYmcD5dTlmOe8gXzMLQaadybQXPnUp5Lsqc");
  digitalWrite(16, HIGH);//desligado
  //  if ((Firebase.setString(firebaseData, "/Controle/" + String(CHAVE), "0")) == true)
  if ((Firebase.setString(firebaseData, "/Controle/" + String(inputname), "0")) == true)
    Serial.println("Zerado");
  //  ESP.wdtDisable();//desabilita wdt por software habilita wdt por hardware de 8 segundos
  delay(500);

}
void loop() {
  leChave(String(inputname),16);
  digitalWrite(port, !digitalRead(port));
  delay(500);

}
