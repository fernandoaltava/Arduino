//com multi rede e ota
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WiFiMulti.h>   // Inclui a biblioteca Wi-Fi-Multi
#include <ESP8266mDNS.h> //necessário para OTA
#include <ArduinoOTA.h> //Ota
const char* OtaHostname = "chacara_1";
const char* OtaSenha = "40224022";
int tempo = 200;
ESP8266WiFiMulti wifiMulti;     // Crie uma instância da classe ESP8266WiFiMulti, chamada 'wifiMulti'
char pay;
String a,b,c,d,e,f,g,h,i,j;
String mypay;
String mytopic;
///////////////////////////
const char* mqtt_server = "192.168.1.81";
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
void setup_zera();
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
  setup_zera();
}
//////////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
  String mytopic(topic);
  String a = String((char)payload[0]);
  String b = String((char)payload[1]);
  String c = String((char)payload[2]);
  String d = String((char)payload[3]);
  String e = String((char)payload[4]);
  String f = String((char)payload[5]);
  String g = String((char)payload[6]);
  String h = String((char)payload[7]);
  String i = String((char)payload[8]);
  String j = String((char)payload[9]);

    String mypay =a+b+c+d+e+f+g+h+i+j;
  //String mypay = String((char)payload[0]);
    Serial.println(mytopic);  /////////////////////
        Serial.println(mypay);
  if (mytopic == "sub_varanda") {
    if (mypay == "1") {
      digitalWrite(16, 1);//pino 16 led invertido low acende porém pino normal low é 0
    } else {
      digitalWrite(16, 0);
    }
  }
  if (mytopic == "sub_lavanderia") {
    if (mypay == "1") {
      digitalWrite(5, 1);//
    } else {
      digitalWrite(5, 0);
    }
  }
  if (mytopic == "home/alarm") {
    if (mypay == "armed_away") {
      digitalWrite(2, 1);//pino 2 led invertido low acende porém pino normal low é 0
    } else if (mypay == "disarmeday"){
      digitalWrite(2, 0);
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
    //client.publish("home/alarm/set", "armed_away");//msg); //("publicacao_do_esp8266", msg);
    //client.publish("home/alarm/", "armed_away");//msg); //("publicacao_do_esp8266", msg);
    //client.publish("home/alarm", "armed_away");//msg); //("publicacao_do_esp8266", msg);
  }
}
//////////////////////////////////////////////////////////////////
void setup_zera() {
  client.publish("pub_varanda", "0");
  client.publish("pub_lavanderia", "0");
  client.publish("pub_cozinha", "0");
  //client.publish("home/alarm","armed_away"); //("subscricao_do_esp8266");//topic
  //client.publish("home/alarm/","armed_away"); //("subscricao_do_esp8266");//topic
  //client.publish("home/alarm/set","armed_away"); //("subscricao_do_esp8266");//topic

}
//////////////////////////////////////////////////////////////////
void setup_wifi() {
  delay(10);
  Serial.println();
  //wifiMulti.addAP("Luana1", "40224022");   // adicione as redes Wi-Fi às quais deseja se conectar
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
      //client.publish("home/alarm", "armed_away"); //("publicacao_do_esp8266", "Olá mundo!");
       //client.publish("home/alarm/", "armed_away"); //("publicacao_do_esp8266", "Olá mundo!");
       //client.publish("home/alarm/set", "armed_away"); //("publicacao_do_esp8266", "Olá mundo!");
      client.subscribe("sub_varanda"); //("subscricao_do_esp8266");//topic
      client.subscribe("sub_lavanderia"); //("subscricao_do_esp8266");//topic
      client.subscribe("sub_cozinha"); //("subscricao_do_esp8266");//topic
      client.subscribe("home/alarm"); //("subscricao_do_esp8266");//topic
      client.subscribe("home/alarm/"); //("subscricao_do_esp8266");//topic
      client.subscribe("home/alarm/set"); //("subscricao_do_esp8266");//topic
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5s");
      delay(5000);
    }
  }
}
//////////////////////////////////////////////////////////////////
/*  PINOS NODEMCU
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
