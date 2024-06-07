#define ID_MQTT  "BCI02"//Informe um ID unico e seu. Caso sejam usados IDs repetidos a ultima conexão irá sobrepor a anterior. 
/////////////////////////////////////////////////////////
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
const uint32_t connectTimeoutMs = 2000;
/////////////////////////////////////////////////////////
#include <PubSubClient.h>
/////////////////////////////////////////////////////////
#define pinLED1 16//(A,a) led inf da placa nodemcu
#define pinLED2 5 //(B,b)
#define pinLED3 4 //(C,c)
#define pinLED4 0 //(D,d)
/////////////////////////////////////////////////////////
#define pinLED5 2 //(0,1) //led sup da placa nodemcu
/////////////////////////////////////////////////////////
#define pinLED6 14//(E,e)
#define pinLED7 12//(F,f)
#define pinLED8 13//(G,g)
#define pinLED9 15//(H,h)
/////////////////////////////////////////////////////////
//WiFi
WiFiClient wifiClient;
/////////////////////////////////////////////////////////
//MQTT Server
const char* BROKER_MQTT = "150.136.173.206"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883;                      // Porta do Broker MQTT
#define TOPIC_SUBSCRIBE1 "teste"//Informe um Tópico único. Caso sejam usados tópicos em duplicidade, o último irá eliminar o anterior.
#define TOPIC_SUBSCRIBE "nodemcu"//Informe um Tópico único. Caso sejam usados tópicos em duplicidade, o último irá eliminar o anterior.
const char* user_MQTT = "fernando";
const char* pass_MQTT = "40224022";
PubSubClient MQTT(wifiClient);// Instancia o Cliente MQTT passando o objeto espClient
/////////////////////////////////////////////////////////
//Declaração das Funções
void mantemConexoes();  //Garante que as conexoes com WiFi e MQTT Broker se mantenham ativas
void conectaWiFi();     //Faz conexão com WiFi
void conectaMQTT();     //Faz conexão com Broker MQTT
void recebePacote(char* topic, byte* payload, unsigned int length);
void desligaTudo();
/////////////////////////////////////////////////////////
void setup() {
  pinMode(pinLED1, OUTPUT);//led inf da placa nodemcu
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);
  pinMode(pinLED4, OUTPUT);
  pinMode(pinLED5, OUTPUT);//led sup da placa nodemcu
  pinMode(pinLED6, OUTPUT);
  pinMode(pinLED7, OUTPUT);
  pinMode(pinLED8, OUTPUT);
  pinMode(pinLED9, OUTPUT);
  /////////////////////  //Wifi multi
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("Recanto Reencontro", "40224022");
  wifiMulti.addAP("Luana", "40224022");
  wifiMulti.addAP("Luana1", "40224022");
  wifiMulti.addAP("Luana2", "40224022");
  wifiMulti.addAP("Belao", "12345678901234567890");
  wifiMulti.addAP("GalaxyA30sAltava", "altava2018");
  /////////////////////
  desligaTudo();
  Serial.begin(115200);
  //conectaWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(recebePacote);
  ESP.wdtDisable();//Habilita wdt por hardware
}
/////////////////////////////////////////////////////////
void loop() {
  ESP.wdtFeed();
  mantemConexoes();
  MQTT.loop();
}
/////////////////////////////////////////////////////////
void mantemConexoes() {
  if (WiFi.status() == !WL_CONNECTED) {
    conectaWiFi(); //se não há conexão com o WiFI, a conexão é refeita
  }
  if (!MQTT.connected()) {
    conectaMQTT();
    //desligaTudo();
  }
}
/////////////////////////////////////////////////////////
void conectaWiFi() {
  ////////ESP.wdtFeed();
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }
  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
    Serial.println();
    Serial.print("Conectado com sucesso, na rede: ");
    Serial.println(WiFi.SSID());
    Serial.print("  IP obtido: ");
    Serial.println(WiFi.localIP());
    ESP.wdtFeed();
  } else {
    Serial.println("WiFi não conectado!");
  }
}
/////////////////////////////////////////////////////////
void conectaMQTT() {
  ////////ESP.wdtFeed();
  while (!MQTT.connected()) {
    Serial.print("Conectando ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    if (MQTT.connect(ID_MQTT, user_MQTT, pass_MQTT)) {
      Serial.println("Conectado ao Broker com sucesso!");
      MQTT.subscribe(TOPIC_SUBSCRIBE);
      MQTT.subscribe(TOPIC_SUBSCRIBE1);
    }
    else {
      Serial.println("Não foi possivel se conectar ao broker.");
      Serial.println("Nova tentativa de conexao em 4s");
      delay(4000);
    }
  }
}
/////////////////////////////////////////////////////////
void desligaTudo()
{
  digitalWrite(pinLED1, LOW); //(A,a)//led inf da placa nodemcu
  digitalWrite(pinLED2, LOW); //(B,b)
  digitalWrite(pinLED3, LOW); //(C,c)
  digitalWrite(pinLED4, LOW); //(D,d)
  digitalWrite(pinLED5, HIGH);//(0,1)//led sup da placa nodemcu
  digitalWrite(pinLED6, LOW); //(E,e)
  digitalWrite(pinLED7, LOW); //(F,f)
  digitalWrite(pinLED8, LOW); //(G,g)
  digitalWrite(pinLED9, LOW); //(H,h)
}
/////////////////////////////////////////////////////////
void recebePacote(char* topic, byte* payload, unsigned int length)
{
  ////////ESP.wdtFeed();
  Serial.println("Topic ok");
  String msg;
  //obtem a string do payload recebido
  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    msg += c;
  }
  if (msg == "A") {
    digitalWrite(pinLED1, HIGH);//led inf da placa nodemcu
    Serial.println("11");
  }
  if (msg == "a") {
    digitalWrite(pinLED1, LOW);//led inf da placa nodemcu
    Serial.println("10");
  }
  if (msg == "B") {
    digitalWrite(pinLED2, HIGH);
    Serial.println("21");
  }
  if (msg == "b") {
    digitalWrite(pinLED2, LOW);
    Serial.println("20");
  }
  if (msg == "C") {
    digitalWrite(pinLED3, HIGH);
    Serial.println("31");
  }
  if (msg == "c") {
    digitalWrite(pinLED3, LOW);
    Serial.println("30");
  }
  if (msg == "D") {
    digitalWrite(pinLED4, HIGH);
    Serial.println("41");
  }
  if (msg == "d") {
    digitalWrite(pinLED4, LOW);
    Serial.println("40");
  }
  if (msg == "0") {
    digitalWrite(pinLED5, HIGH);//led sup da placa nodemcu
    Serial.println("00");
  }
  if (msg == "1") {
    digitalWrite(pinLED5, LOW);//led sup da placa nodemcu
    Serial.println("01");
  }
  //ESP.wdtFeed();
  if (msg == "E") {
    digitalWrite(pinLED6, HIGH);
    Serial.println("61");
  }
  if (msg == "e") {
    digitalWrite(pinLED6, LOW);
    Serial.println("60");
  }
  if (msg == "F") {
    digitalWrite(pinLED7, HIGH);
    Serial.println("71");
  }
  if (msg == "f") {
    digitalWrite(pinLED7, LOW);
    Serial.println("70");
  }
  if (msg == "G") {
    digitalWrite(pinLED8, HIGH);
    Serial.println("81");
  }
  if (msg == "g") {
    digitalWrite(pinLED8, LOW);
    Serial.println("80");
  }
  if (msg == "H") {
    digitalWrite(pinLED9, HIGH);
    Serial.println("91");
  }
  if (msg == "h") {
    digitalWrite(pinLED9, LOW);
    Serial.println("90");
  }
  ////////ESP.wdtFeed();
}
