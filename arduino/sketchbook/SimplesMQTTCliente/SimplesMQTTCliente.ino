#include "EspMQTTClient.h"
EspMQTTClient client(
  "Luana",
  "40224022",
  "192.168.1.157",  // MQTT Broker server ip
  "fernando",       // Can be omitted if not needed
  "40224022",       // Can be omitted if not needed
  "NodeMCU_1",     // Nome do cliente que identifica exclusivamente o seu dispositivo
  1883              // MQTT porta
);
//WiFi.macAddress();

void achar();


void setup()
{
  pinMode(D0, OUTPUT); //led contrário ao pino
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT); //led contrário ao pino
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  //3,3
  //gnd
  pinMode(D5, INPUT_PULLUP); //se 0 manda Meencontra
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
  pinMode(D8, INPUT_PULLUP);
  //rx
  //tx
  //gnd
  //3,3
  if (D5 == 0)achar();
  digitalWrite(D0, 0);
  //Serial.begin(115200);
  // Funcionalidades opcionais do EspMQTTClient:
  //  client.enableDebuggingMessages();// Habilita mensagens de depuração enviadas para saída serial
  //  client.enableHTTPWebUpdater(); // Habilite o atualizador da web. Usuário e senha padrão para valores de MQTTUsername e MQTTPassword. Eles podem ser substituídos por enableHTTPWebUpdater ("usuário", "senha").
  //  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");// Você pode ativar o sinalizador de retenção definindo o terceiro parâmetro como verdadeiro
}
// Esta função é chamada assim que tudo estiver conectado (Wifi e MQTT)
// AVISO: VOCÊ DEVE IMPLEMENTA-LO SE UTILIZAR EspMQTTClient
void onConnectionEstablished()
{
  // Inscreva-se em "mytopic / test" e exiba a mensagem recebida em Serial
  //client.subscribe("mytopic/test", [](const String & payload) {
  client.subscribe(WiFi.macAddress(), [](const String & payload) {
    //Serial.println(payload);
    if (payload == "on" || payload == "ON") {
      digitalWrite(D0, 0);
    }
    if (payload == "off" || payload == "OFF") {
      digitalWrite(D0, 1);
    }

  });
  // Inscreva-se em "mytopic/wildcardtest/#" e exiba a mensagem recebida em Serial
  client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
    //Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });
  // Publica uma mensagem em "mytopic/test"
  client.publish("mytopic/test", "This is a message"); // Você pode ativar o sinalizador de retenção definindo o terceiro parâmetro como verdadeiro
  // Executar instruções atrasadas
  client.executeDelayed(5 * 1000, []() {
    client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");
  });
}
void loop()
{
  client.loop();

}
void achar() {
  client.publish("Meencontre", WiFi.macAddress());
  delay(1000);
}
/*
  D0-gpio16 /led pull-down
  D1-gpio5       pull-up
  D2-gpio4  /led pull-up
  D3-gpio0       pull-up
  D4-gpio2       pull-up
  3,3v
  gnd
  D5-gpio14      pull-up
  D6-gpio12      pull-up
  D7-gpio13      pull-up
  D8-gpio15      pull-up
  Rx-gpio3       pull-up
  Tx-gpio1       pull-up
  gnd
  3,3v
*/
