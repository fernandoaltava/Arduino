/* SimpleMQTTClient.ino
   O objetivo deste exemplo é ilustrar um manuseio simples de conexão MQTT e Wifi.
   Depois de se conectar com sucesso a uma rede Wifi e a um broker MQTT, ele se inscreve em um tópico e envia uma mensagem a ele.
   Ele também enviará uma mensagem com atraso de 5 segundos depois.*/
#include "EspMQTTClient.h"
EspMQTTClient client(
  "Luana",
  "40224022",
  //"altava.duckdns.org",  // MQTT Broker server ip
  "170.81.152.95",
  "fernando",//MQTTUsername",   // Pode ser omitido se não for necessário
  "40224022",//MQTTPassword",   // Pode ser omitido se não for necessário
  "TestClient",     // Nome do cliente que identifica exclusivamente o seu dispositivo
  1883              // A porta MQTT, padrão para 1883. esta linha pode ser omitida
);
void setup()
{
  Serial.begin(115200);
  // Funcionalidades opcionais de EspMQTTClient :
//  client.enableDebuggingMessages(); // Ativar mensagens de depuração enviadas para saída serial
//  client.enableHTTPWebUpdater(); // Habilite o atualizador da web. Usuário e senha padrão para valores de MQTTUsername e MQTTPassword. Eles podem ser substituídos por enableHTTPWebUpdater ("usuário", "senha").
//  client.enableLastWillMessage("TestClient/lastwill", "Estou em offline");  // Você pode ativar o sinalizador de retenção definindo o terceiro parâmetro como verdadeiro
}
// Esta função é chamada assim que tudo estiver conectado (Wifi e MQTT)
// AVISO: VOCÊ DEVE IMPLEMENTA-LO SE UTILIZAR EspMQTTClient
void onConnectionEstablished()
{
  // Inscreva-se em "mytopic/test" e exiba a mensagem recebida em Serial
  client.subscribe("mytopic/test", [](const String & payload) {
    Serial.println(payload);
  });
  // Inscreva-se em "mytopic/wildcardtest/#" e exiba a mensagem recebida em Serial
  client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  });
  // Publique uma mensagem para "mytopic/test"
  client.publish("mytopic/test", "Esta é a mensagem"); // Você pode ativar o sinalizador de retenção definindo o terceiro parâmetro como verdadeiro
  // Executar instruções atrasadas
  client.executeDelayed(5 * 1000, []() {
    client.publish("mytopic/wildcardtest/test123", "Esta é uma mensagem enviada 5 segundos depois");
  });
}
void loop()
{
  client.loop();
}
