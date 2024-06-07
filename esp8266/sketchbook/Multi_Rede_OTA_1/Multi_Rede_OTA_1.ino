#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
////////////////////////////////
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(172, 16, 0, 100);
IPAddress server(172, 16, 0, 2);
////////////////////////////////

ESP8266WiFiMulti wifiMulti;     // Crie uma instância da classe ESP8266WiFiMulti, chamada 'wifiMulti'

const byte led = 13;
//////////////////////////////////////////////////
// Cabeçalho da função CallBack
void callback(char* topic, byte* payload, unsigned int length);
EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);
// Função CallBack
void callback(char* topic, byte* payload, unsigned int length) {
  // Para republicar esta carga útil, uma cópia deve ser feita
  // já que o buffer de carga útil original será sobrescrito enquanto
  // construindo o pacote PUBLICAR.
  // Alocar a quantidade correta de memória para a cópia da carga útil
  byte* p = (byte*)malloc(length);
  // Copie a carga útil para o novo buffer
  memcpy(p, payload, length);
  client.publish("outTopic", p, length);
  // Liberte a memória
  free(p);
}
//////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);         // Inicie a comunicação serial para enviar mensagens ao computador
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("Luana", "40224022");   // adicione as redes Wi-Fi às quais deseja se conectar
  wifiMulti.addAP("Recanto Reencontro", "40224022");
//  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Conectando ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Aguarde até que o Wi-Fi se conecte
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Conectado em ");
  Serial.println(WiFi.SSID());              // Diga-nos a qual rede estamos conectados
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Envie o endereço IP do ESP8266 para o computador

  ArduinoOTA.setHostname("ESP8266");
  ArduinoOTA.setPassword("esp8266");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready");

  pinMode(led, OUTPUT);
  digitalWrite(led, 1);

  if (client.connect("altava.duckdns.org", "fernando", "40224022")) {
    client.publish("outTopic", "hello world");
    client.subscribe("inTopic");
  }
}

unsigned long previousTime = millis();
const unsigned long interval = 1000;

void loop() {
  ArduinoOTA.handle();
  unsigned long diff = millis() - previousTime;
  if (diff > interval) {
    digitalWrite(led, !digitalRead(led));  // Altere o estado do LED
    previousTime += diff;
  }
  client.loop();
}
