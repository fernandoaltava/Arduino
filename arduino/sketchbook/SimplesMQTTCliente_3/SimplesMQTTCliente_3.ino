#include <Thread.h>
#include <ThreadController.h>

ThreadController cpu;
Thread threadOnLine;
Thread threadOffLine;

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
String mensagem;
//WiFi.macAddress();
////////////////////////////////////////////////////////////////////////////
void achar();
void saidas();
void vepinos();
void online();
void offline();
////////////////////////////////////////////////////////////////////////////
void setup()
{
  threadOnLine.setInterval(500);
  threadOnLine.onRun(online);
  threadOffLine.setInterval(1000);
  threadOffLine.onRun(offline);

  cpu.add(&threadOnLine);
  cpu.add(&threadOffLine);

  pinMode(D0, OUTPUT);//led contrário ao pino
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);//led contrário ao pino
  //3,3
  //gnd
  pinMode(D5, INPUT_PULLUP);//se 0 manda Meencontra
  pinMode(D6, INPUT_PULLUP);//se 0
  pinMode(D7, INPUT_PULLUP);//se 0
  pinMode(D8, INPUT);       //se 1
  //rx
  //tx
  //gnd
  //3,3
  digitalWrite(D0, 0);
  digitalWrite(D1, 0);
  digitalWrite(D2, 0);
  digitalWrite(D3, 0);
  digitalWrite(D4, 0);
  //online();
  Serial.begin(115200);
}
////////////////////////////////////////////////////////////////////////////
void onConnectionEstablished()
{
  client.subscribe(WiFi.macAddress(), [](const String & payload) {
    mensagem = payload;
    saidas();
  });
}
////////////////////////////////////////////////////////////////////////////
void loop()
{
  cpu.run();
  //client.publish(WiFi.macAddress(), "OK");
  client.loop();
  if (digitalRead(D5) == 0) {
    achar();
    vepinos();
  }
  if (digitalRead(D6) == 0) {
    client.publish(WiFi.macAddress() + "/d6", "Acionado",true); // Você pode ativar o sinalizador de retenção definindo o terceiro parâmetro como verdadeiro
    delay(500);
    client.publish(WiFi.macAddress() + "/d6", " ",true);
  }
  if (digitalRead(D7) == 0) {
    client.publish(WiFi.macAddress() + "/d7", "Acionado",true); // Você pode ativar o sinalizador de retenção definindo o terceiro parâmetro como verdadeiro
    delay(500);
    client.publish(WiFi.macAddress() + "/d7", " ",true);
  }
  if (digitalRead(D8) == 1) {
    client.publish(WiFi.macAddress() + "/d8", "Acionado",true); // Você pode ativar o sinalizador de retenção definindo o terceiro parâmetro como verdadeiro
    delay(500);
    client.publish(WiFi.macAddress() + "/d8", " ",true);
  }
}
////////////////////////////////////////////////////////////////////////////
void online() {
  client.publish(WiFi.macAddress() , "OK",true);
  //  client.publish(WiFi.macAddress() + "/d6", "On");
  //  client.publish(WiFi.macAddress() + "/d7", "On");
  //  client.publish(WiFi.macAddress() + "/d8", "On");
}
////////////////////////////////////////////////////////////////////////////
void offline() {
  client.publish(WiFi.macAddress() , "  ",true);
  //  client.publish(WiFi.macAddress() + "/d6", "Off");
  //  client.publish(WiFi.macAddress() + "/d7", "Off");
  //  client.publish(WiFi.macAddress() + "/d8", "Off");
}
////////////////////////////////////////////////////////////////////////////
void vepinos() {
  Serial.print("Pino D5  ");
  Serial.println(digitalRead(D5));
  Serial.print("Pino D6  ");
  Serial.println(digitalRead(D6));
  Serial.print("Pino D7  ");
  Serial.println(digitalRead(D7));
  Serial.print("Pino D8  ");
  Serial.println(digitalRead(D8));
  Serial.println(WiFi.macAddress());
  delay(200);
}
////////////////////////////////////////////////////////////////////////////
void saidas() {
  if (mensagem == "d0on")digitalWrite(D0, 1);
  if (mensagem == "d0off")digitalWrite(D0, 0);
  if (mensagem == "d1on")digitalWrite(D1, 1);
  if (mensagem == "d1off")digitalWrite(D1, 0);
  if (mensagem == "d2on")digitalWrite(D2, 1);
  if (mensagem == "d2off")digitalWrite(D2, 0);
  if (mensagem == "d3on")digitalWrite(D3, 1);
  if (mensagem == "d3off")digitalWrite(D3, 0);
  if (mensagem == "d4on")digitalWrite(D4, 1);
  if (mensagem == "d4off")digitalWrite(D4, 0);
  delay(50);
}
////////////////////////////////////////////////////////////////////////////
void achar() {
  client.publish("Meencontre", WiFi.macAddress(), true);
  delay(1000);
}
////////////////////////////////////////////////////////////////////////////
/*
  15  D0-gpio16 /led pull-down
  14  D1-gpio5       pull-up
  13  D2-gpio4  /led pull-up
  12  D3-gpio0       pull-up
  11  D4-gpio2       pull-up
  10  3,3v
  9   gnd
  8   D5-gpio14      pull-up
  7   D6-gpio12      pull-up
  6   D7-gpio13      pull-up
  5   D8-gpio15      pull-up
  4   Rx-gpio3       pull-up
  3   Tx-gpio1       pull-up
  2   gnd
  1   3,3v

  //client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
  //  Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
  //});
  //client.publish("mytopic/test", "This is a message"); // Você pode ativar o sinalizador de retenção definindo o terceiro parâmetro como verdadeiro
  //client.executeDelayed(5 * 1000, []() {
  //  client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");
  //});




*/
