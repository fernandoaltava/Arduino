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
   Ler()
   Ler_A()
   Pino *pino1(13, OUTPUT);//mode 0 OUTPUT o * indica ponteiro//instancia objeto
   Pino pino2(12, OUTPUT);//instancia objeto
   Pino pino3(2, INPUT_PULLUP);//instancia objeto
   pino1->Inverter();// -> faz o apontamento pois pino1 é um ponteiro
   pino2.Inverter();//pino 2 não precisa de -> pois não é um ponteiro
*/
#include <ESP.h>;
#include "Pino.h"
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
#include <PubSubClient.h>

#include "NTPClient.h"
#include "WiFiUdp.h"
const long utcOffsetInSeconds = -10800;
char daysOfTheWeek[7][12] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

const char *ssid1 = "Luana2";
const char *password1 = "40224022";
const char *ssid2 = "Recanto Reencontro";
const char *password2 = "40224022";
const char *ssid3 = "Luana";
const char *password3 = "40224022";
const char *mqtt_server = "132.145.172.205";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
int flag;
const IPAddress remote_ip(8, 8, 8, 8);//endereço do google
unsigned long testDuration = 3500;
Pino pino2(2, OUTPUT);
Pino pino16(16, OUTPUT);
Pino pino5(5, OUTPUT);
Pino pino4(4, OUTPUT);
Pino pino0(0, OUTPUT);
Pino pino14(14, OUTPUT);
//////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
  //pino2.Inverter();
  //pino2.Piscar(500, 50);
  int t = 100000;
  Serial.print("A mensagem chegou [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
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
  ESP.wdtFeed();//Zera a contagem do wdt
}
//////////////////////////////////////////////////////////////
void dados();
void estado();
void zera();
void mudaRede();
//////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  estado();
  timeClient.begin();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while (WiFi.status() == WL_DISCONNECTED) {
    mudaRede();
  }
  Serial.println("Conectado");
  ESP.wdtDisable();
  zera();
}
//////////////////////////////////////////////////////////////
void loop() {
  unsigned long prevTime = millis();
  while (millis() - prevTime < testDuration) {
    if (!Ping.ping("www.google.com", 1) || !client.connected()) { //se não conseguir pingar o Google
      Serial.print("Sem Internet ");//esta sem internet
      mudaRede();//inicia nova conexão
    } else {//se conseguir pingar o Google, esta conectado ao wifi e internet
      //aqui deve ser colocado o programa principal
      pino16.Piscar(500, 50);
      client.loop();
      unsigned long now = millis();
      if (now - lastMsg > 500) {
        lastMsg = now;
        ++value;
        snprintf (msg, MSG_BUFFER_SIZE, " %ld", value);
        Serial.print("Publicando menssagem: ");
        dados();
        Serial.println(msg);
        //client.publish("teste1", msg);
      }
    }
    ESP.wdtFeed();//Zera a contagem do wdt
  }
}
//////////////////////////////////////////////////////////////
void mudaRede() {
  Serial.println("Mudando de Wifi");//esta sem internet
  int flag = 1;
  //int x = 100000;
  int y = 6000;
  pino2.Piscar(500, 50);
  Serial.println("Procurando rede .....");
  int rede = WiFi.scanNetworks();
  for (int i = 0; i < rede; i++) {
    switch (flag) {
      case 1:
        flag = 2;
        if (WiFi.SSID(i) == ssid1) {
          WiFi.begin(ssid1, password1);
          delay(y);
          Serial.println(" Wifi1 encontrada");
        }
      case 2:
        flag = 3;
        if (WiFi.SSID(i) == ssid2) {
          WiFi.begin(ssid2, password2);
          delay(y);
          Serial.println(" Wifi2 encontrada");
        }
      case 3:
        flag = 1;
        if (WiFi.SSID(i) == ssid3) {
          WiFi.begin(ssid3, password3);
          delay(y);
          Serial.println(" Wifi3 encontrada");
        }
    }
  }
  if (client.connect("arduinoClient", "fernando", "40224022")) {
    //client.publish("teste1", "hello world");
    client.publish("teste3", "XXXX");
    client.publish("teste4", "XXXX");
    client.publish("teste5", "XXXX");
    client.publish("teste6", "XXXX");
    ESP.wdtFeed();//Zera a contagem do wdt
    delay(200);
    dados();
  }
  Serial.println("Internet conectada");
  Serial.print("Conectado a:  ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}
void dados() {
  client.publish("teste3", (WiFi.SSID().c_str()));
  client.publish("teste4", (WiFi.localIP().toString().c_str()));
  client.subscribe("teste2");
  client.publish("teste5", (daysOfTheWeek[timeClient.getDay()]));
  client.publish("teste6", (timeClient.getFormattedTime().c_str()));
}
void estado() {
  pino5.Ligar();
  pino4.Ligar();
  pino0.Ligar();
  pino14.Ligar();
}
void zera() {
  client.publish("teste2", "1"); delay(100);
  client.publish("teste2", "3"); delay(100);
  client.publish("teste2", "5"); delay(100);
  client.publish("teste2", "7"); delay(100);
}
