
/*Funcionando com troca de rede e conexão com mqtt 20/09/2022 21:22
  Funcionando WDT 21/09/2022 16:22
  Funcionando com NTP 29/09/2022 13:21
*/
//////////////////////////////////////////////////////////////
/* -----------Metodos da classe Pino-------------------
   Ligar()
   Desligar()
   Inverter()
   Ligar_t(int tmp)
   Desligar_t(int tmp)
   Piscar(int tmpA, int tmpB)
   Clique(funcao)
   Ler_D()
   Ler_A()
   Pino *pino1(13, OUTPUT);//mode 0 OUTPUT o * indica ponteiro//instancia objeto
   Pino pino2(12, OUTPUT);//instancia objeto
   Pino pino3(2, INPUT_PULLUP);//instancia objeto
   pino1->Inverter();// -> faz o apontamento pois pino1 é um ponteiro
   pino2.Inverter();//pino 2 não precisa de -> pois não é um ponteiro
*/
//#include<stdio.h>
//#include<stdlib.h>
#include <ESP.h>;
#include "classe.h"//minha classe para pinos
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <PubSubClient.h>
#include <NTPClient_Generic.h>
#include <Servo.h>
Servo myservo;
#include "WiFiUdp.h"
WiFiUDP ntpUDP;
#define TIME_ZONE_OFFSET_HRS            (-3)
NTPClient timeClient(ntpUDP);
int payservo = 0;
const char *ssid2 = "Luana";
const char *password2 = "40224022";
const char *ssid1 = "RecantoReencontro";
const char *password1 = "40224022";
//const char *ssid3 = "Luana";
//const char *password3 = "40224022";
const char *mqtt_server = "132.145.172.205";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
char msg1;
int value = 0;
int flag = 1;
//////////////////////////////////////////////////////////////
const char *topicServo =/*           */"servo2";//Estes parametros devem
const char *topicRele =/*             */"rele2";//ser alterados para cada
const char *topicIp =/*                 */"ip2";//placa a ser utilizada
const char *topicRede =/*             */"rede2";
const char *topicHora =/*             */"hora2";
const char *topicData =/*             */"data2";
const char *topicCont =/*             */"cont2";
const char *topicAnalog =/*         */"analog2";
const char *topicClient =/* */ "arduinoClient2";
//////////////////////////////////////////////////////////////
const IPAddress remote_ip(8, 8, 8, 8);//endereço do google
unsigned long testDuration = 3500;
Pino pino2(2, OUTPUT);
Pino pino16(16, OUTPUT);
Pino pino5(5, OUTPUT);
Pino pino4(4, OUTPUT);
Pino pino0(0, OUTPUT);
Pino pino14(14, OUTPUT);
Pino pinoA0(A0, INPUT);
//////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
  int t = 100000;
  Serial.print("A mensagem chegou [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  String mytopic = String(topic);
  Serial.print("mytopic   >");
  Serial.println(mytopic);
  payservo = ((int)payload[0]);
  if (mytopic == topicServo) { //"servo1") {
    myservo.write(payservo);
    delay(150);
    Serial.println("servo    !");
  } else if (mytopic == topicRele) { //"rele2") {
    Serial.println("rele    !");
    switch ((char)payload[0]) {
      case '0':
        pino5.Ligar();
        delayMicroseconds(t);
        break;
      case '1':
        pino5.Desligar();
        delayMicroseconds(t);
        break;
      case '2':
        pino4.Ligar();
        delayMicroseconds(t);
        break;
      case '3':
        pino4.Desligar();
        delayMicroseconds(t);
        break;
      case '4':
        pino0.Ligar();
        delayMicroseconds(t);
        break;
      case '5':
        pino0.Desligar();
        delayMicroseconds(t);
        break;
      case '6':
        pino14.Ligar();
        delayMicroseconds(t);
        break;
      case '7':
        pino14.Desligar();
        delayMicroseconds(t);
        break;
    }
  }
  ESP.wdtFeed();//Zera a contagem do wdt
  pino2.Inverter();
}
//////////////////////////////////////////////////////////////
void dados();
void estado();
void zera();
void mudaRede();
//////////////////////////////////////////////////////////////
void setup() {
  myservo.attach(12);
  Serial.begin(115200);
  estado();
  timeClient.begin();
  timeClient.setTimeOffset(3600 * TIME_ZONE_OFFSET_HRS);
  timeClient.setUpdateInterval(SECS_IN_HR);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while (WiFi.status() == WL_DISCONNECTED) {
    mudaRede();
  }
  Serial.println("Conectado");
  ESP.wdtDisable();
  zera();
}
//////////////////////////////////////////////////////////////altava.duckdns.org
void loop() {
  unsigned long prevTime = millis();
  while (millis() - prevTime < testDuration) {
    if (!Ping.ping("www.google.com.br", 1) /*|| !Ping.ping("www.itau.com.br", 1) || !client.connected()*/) { //se não conseguir pingar o Google N° de pings
      //if (!Ping.ping("altava.duckdns.org", 1) || !client.connected()) { //se não conseguir pingar o Google
      Serial.print("Sem Internet ");//esta sem internet
      mudaRede();//inicia nova conexão
    } else {//se conseguir pingar o Google, esta conectado ao wifi e internet
      //aqui deve ser colocado o programa principal

      //int avg_time_ms = Ping.averageTime();//Depois que `Ping.ping()` foi chamado, o tempo médio de resposta (em milissegundos) pode ser recuperado com

      pino16.Piscar(500, 50);
      timeClient.update();
      client.loop();
      unsigned long now = millis();
      if (now - lastMsg > 500) {
        lastMsg = now;
        ++value;
        snprintf (msg, MSG_BUFFER_SIZE, " %ld", value);
        Serial.print("Publicando menssagem: ");
        dados();
        Serial.println(msg);
        int voltage = map(analogRead(A0), 0, 1023, 0, 255);
        Serial.println(voltage);
        client.publish(topicCont, msg);
        client.publish(topicAnalog, String(map(analogRead(A0), 0, 255, 0, 1023)).c_str());
      }
    }
    ESP.wdtFeed();//Zera a contagem do wdt
  }
}
//////////////////////////////////////////////////////////////
void mudaRede() {
  Serial.println("Mudando de Wifi");//esta sem internet
  //int flag = 1;
  int y = 5000;
  Serial.println("Procurando rede .....");
  int rede = WiFi.scanNetworks();
  for (int i = 0; i < rede; i++) {
    switch (flag) {
      case 1:
        flag = 2;
        if (WiFi.SSID(i) == ssid1) {
          WiFi.begin(ssid1, password1);
          delay(y);
          ESP.wdtFeed();//Zera a contagem do wdt
          Serial.println(" Wifi1 encontrada");
        } break;
      case 2:
        flag = 1;
        if (WiFi.SSID(i) == ssid2) {
          WiFi.begin(ssid2, password2);
          delay(y);
          ESP.wdtFeed();//Zera a contagem do wdt
          Serial.println(" Wifi2 encontrada");
        } break;
        //      case 3:
        //        flag = 1;
        //        if (WiFi.SSID(i) == ssid3) {
        //          WiFi.begin(ssid3, password3);
        //          delay(y);
        //          ESP.wdtFeed();//Zera a contagem do wdt
        //          Serial.println(" Wifi3 encontrada");
        //        } break;
    }
  }
  if (client.connect(topicClient, "fernando", "40224022")) {
    client.publish(topicIp, "XXXX"); //("teste3", "XXXX");
    client.publish(topicRede, "XXXX"); //("teste4", "XXXX");
    client.publish(topicData, "XXXX"); //("teste5", "XXXX");
    client.publish(topicHora, "XXXX"); //("teste6", "XXXX");
    client.publish(topicRede, (WiFi.SSID().c_str()));
    client.publish(topicIp, (WiFi.localIP().toString().c_str()));
    ESP.wdtFeed();//Zera a contagem do wdt
    delay(200);
    dados();
  }
  Serial.println("Internet conectada");
  Serial.print("Conectado a:  ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  value = 0;
  ESP.wdtFeed();//Zera a contagem do wdt
}
void dados() {
  //client.publish(topicRede, (WiFi.SSID().c_str()));
  //client.publish(topicIp, (WiFi.localIP().toString().c_str()));
  client.subscribe(topicRele);
  client.subscribe(topicServo);
  client.publish(topicData, ((timeClient.getDoW() + " " + timeClient.getDay() + "/" + timeClient.getMonth() + "/" + timeClient.getYear()).c_str()));
  client.publish(topicHora, ((timeClient.getStrHours() + ":" + timeClient.getStrMinutes() + ":" + timeClient.getStrSeconds()).c_str()));
  ESP.wdtFeed();//Zera a contagem do wdt
}
void estado() {
  pino5.Desligar();
  pino4.Desligar();
  pino0.Desligar();
  pino14.Desligar();
}
void zera() {
  client.publish(topicRele, "1"); delay(100);
  client.publish(topicRele, "3"); delay(100);
  client.publish(topicRele, "5"); delay(100);
  client.publish(topicRele, "7"); delay(100);
  ESP.wdtFeed();//Zera a contagem do wdt
}
