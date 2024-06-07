//com multi rede e ota
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266WiFiMulti.h>   // Inclui a biblioteca Wi-Fi-Multi
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
//char Hostname = "varanda"; ///< Hostname. The setup function adds the Chip ID at the end.
const char* OtaHostname = "varanda";
const char* OtaSenha = "40224022";
int tempo = 200;
ESP8266WiFiMulti wifiMulti;     // Crie uma instância da classe ESP8266WiFiMulti, chamada 'wifiMulti'
///////////////////////////
const char* ssid = "Luana";
const char* password = "40224022";
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
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  setup_ota();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  ESP.wdtEnable(1000);
}
//////////////////////////////////////////////////////////////////
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
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
    client.publish("pub_varanda", msg); //("publicacao_do_esp8266", msg);
  }
}
//////////////////////////////////////////////////////////////////
void setup_wifi() {
  delay(10);
  Serial.println();
  wifiMulti.addAP("Luana", "40224022");   // aadicione as redes Wi-Fi às quais deseja se conectar
  wifiMulti.addAP("Recanto Reencontro", "40224022");
  while (wifiMulti.run() != WL_CONNECTED) { // Aguarde a conexão do Wi-Fi: procure redes Wi-Fi e conecte-se à mais forte das redes acima
    delay(tempo);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Conectado em ");
  Serial.println(WiFi.SSID());              // Diga-nos a qual rede estamos conectados
  Serial.print("Endereço IP:\t");
  Serial.println(WiFi.localIP());           // Envie o endereço IP do ESP8266 para o computador
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
/*  ArduinoOTA.onEnd([]() {
    delay(tempo);
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    delay(tempo);
    Serial.printf("Progresso: %u%%\r", (progress / (total / 100)));
    delay(tempo);
  });
  ArduinoOTA.onError([](ota_error_t error) {
    delay(tempo);
    Serial.printf("Erro[%u]: ", error);
    delay(tempo);
    if (error == OTA_AUTH_ERROR) Serial.println("Autenticação Falhou!");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Iniciando Falhou");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Conexão Falhou");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Recepção Falhou");
    else if (error == OTA_END_ERROR) Serial.println("Falha geral");
  });*/
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
      client.publish("pub_varanda", "Ola Mundo!"); //("publicacao_do_esp8266", "Olá mundo!");
      client.subscribe("sub_varanda"); //("subscricao_do_esp8266");//topic
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5s");
      delay(5000);
    }
  }
}
//////////////////////////////////////////////////////////////////
