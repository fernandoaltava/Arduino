/*
  Exemplo básico de MQTT com autenticação
   - conecta-se a um servidor MQTT, fornecendo nome de usuário
     e senha
   - publica "hello world" no tópico "outTopic"
   - inscreve-se no tópico "inTopic"
*/
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
// Atualize-os com valores adequados para sua rede.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(172, 16, 0, 100);
IPAddress server(172, 16, 0, 2);
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
  memcpy(p,payload,length);
  client.publish("outTopic", p, length);
  // Liberte a memória
  free(p);
}
void setup()
{
  Ethernet.begin(mac, ip);
   // Nota - o tamanho máximo do pacote padrão é 128 bytes. Se o
   // comprimento combinado de clientId, nome de usuário e senha excedem este use o
   // seguindo para aumentar o tamanho do buffer:
   // client.setBufferSize (255);
  if (client.connect("arduinoClient", "testuser", "testpass")) {
    client.publish("outTopic","hello world");
    client.subscribe("inTopic");
  }
}
void loop()
{
  client.loop();
}
