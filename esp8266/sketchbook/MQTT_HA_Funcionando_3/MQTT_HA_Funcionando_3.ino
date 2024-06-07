//com multi rede e ota
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WiFiMulti.h>   // Inclui a biblioteca Wi-Fi-Multi
#include <ESP8266mDNS.h> //necessário para OTA
#include <ArduinoOTA.h> //Ota
//char Hostname = "varanda"; ///< Hostname. The setup function adds the Chip ID at the end.
const char* OtaHostname = "varanda";
const char* OtaSenha = "40224022";
int tempo = 200;
ESP8266WiFiMulti wifiMulti;     // Crie uma instância da classe ESP8266WiFiMulti, chamada 'wifiMulti'
char pay;
String mypay;
String mytopic;
///////////////////////////
//const char* ssid = "Luana";
//const char* password = "40224022";
const char* mqtt_server = "altava.duckdns.org";
const char* mqtt_user = "fernando";
const char* mqtt_passwd = "40224022";
///////////////////////////
WiFiClient espClient;//instancia como espClient
///////////////////////////
PubSubClient client(espClient);
///////////////////////////
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
//////////////////////////////////////////////////////////////////
void reconnect();
void setup_wifi();
void setup_ota();
//////////////////////////////////////////////////////////////////
void setup() {
  ESP.wdtDisable();//desabilita wdt por software habilita wdt por hardware de 8 segundos
  pinMode(16, OUTPUT);//pino varanda
  pinMode(5, OUTPUT);//pino lavanderia
  pinMode(2, OUTPUT);//pino cozinha
  Serial.begin(115200);
  setup_wifi();
  setup_ota();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  ESP.wdtEnable(true);
}
//////////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Mensagem recebida [");
  String mytopic(topic);
//  Serial.print(topic);
//  Serial.println("] ");
  String mypay = String((char)payload[0]);
/////////////////////
  if (mytopic == "sub_varanda") {
    if (mypay == "1") {
      digitalWrite(16, LOW);//pino 16 led invertido low acende porém pino normal low é 0
//      Serial.println("Pino 16 low");
    } else {
      digitalWrite(16, HIGH);
//      Serial.println("Pino 16 high");
    }
  }
  if (mytopic == "sub_lavanderia") {
    if (mypay == "1") {
      digitalWrite(5, LOW);//
//      Serial.println("Pino 5 low");
    } else {
      digitalWrite(5, HIGH);
//      Serial.println("Pino 5 high");
    }
  }
  if (mytopic == "sub_cozinha") {
    if (mypay == "1") {
      digitalWrite(2, LOW);//pino 2 led invertido low acende porém pino normal low é 0
//      Serial.println("Pino 2 low");
    } else {
      digitalWrite(2, HIGH);
//      Serial.println("Pino 2 high");
    }
  }
/////////////////////  
}
//////////////////////////////////////////////////////////////////
void loop() {
  ArduinoOTA.handle();
  ESP.wdtFeed();//zera a contagem do watchdog
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "Olá mundo! #%ld", value);
    Serial.print("Publica mensagem: ");
    Serial.println(msg);
    client.publish("pub_chacara", msg); //("publicacao_do_esp8266", msg);
//    client.publish("pub_lavanderia", msg); //("publicacao_do_esp8266", msg);
//    client.publish("pub_cozinha", msg); //("publicacao_do_esp8266", msg);
  }
}
//////////////////////////////////////////////////////////////////
void setup_wifi() {
  delay(10);
  Serial.println();
  wifiMulti.addAP("Luana1", "40224022");   // adicione as redes Wi-Fi às quais deseja se conectar
  wifiMulti.addAP("Luana2", "40224022");   // adicione as redes Wi-Fi às quais deseja se conectar
//  wifiMulti.addAP("Luana", "40224022");
  while (wifiMulti.run() != WL_CONNECTED) { // Aguarde a conexão do Wi-Fi: procure redes Wi-Fi e conecte-se à mais forte das redes acima
    delay(tempo);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Conectado em ");
  Serial.println(WiFi.SSID());              // Diga-nos a qual rede estamos conectados
  Serial.print("Endereço IP:\t");
  Serial.println(WiFi.localIP());           // Envie o endereço IP do ESP8266 para o computador
  Serial.print("STA MAC: ");
  Serial.println(WiFi.macAddress());
}
//////////////////////////////////////////////////////////////////
void setup_ota() {
  ArduinoOTA.setHostname(OtaHostname);
  delay(tempo);
  ArduinoOTA.setPassword(OtaSenha);
  delay(tempo);
  ArduinoOTA.onStart([]() {
    delay(tempo);
  });
  ArduinoOTA.begin();
  delay(tempo);
  ArduinoOTA.handle();
  delay(tempo);
}
//////////////////////////////////////////////////////////////////
void reconnect() {
  while (!client.connected()) {
    Serial.println("Aguardando conexão MQTT...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_passwd)) { //topic,mensagem
      Serial.println("conectado");
      client.publish("pub_chacara", "Ola Mundo!"); //("publicacao_do_esp8266", "Olá mundo!");
      client.subscribe("sub_varanda"); //("subscricao_do_esp8266");//topic
      client.subscribe("sub_lavanderia"); //("subscricao_do_esp8266");//topic
      client.subscribe("sub_cozinha"); //("subscricao_do_esp8266");//topic
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5s");
      delay(5000);
    }
  }
}
//////////////////////////////////////////////////////////////////
/*
  15  D0-gpio 16 /led pull-down usar como saída DEEP-SLEEP varanda
  14  D1-gpio 5       pull-up   usar como saída            lavanderia
  13  D2-gpio 4       pull-up   usar como saída            cozinha
  12  D3-gpio 0       pull-up   somente saída
  11  D4-gpio 2  /led pull-up   somente saída
  10  3,3v
  9   gnd
  8   D5-gpio 14      pull-up   usar como entrada
  7   D6-gpio 12      pull-up   usar como entrada
  6   D7-gpio 13      pull-up   usar como entrada
  5   D8-gpio 15                somente saída
  4   Rx
  3   Tx
  2   gnd
  1   3,3v
*/
