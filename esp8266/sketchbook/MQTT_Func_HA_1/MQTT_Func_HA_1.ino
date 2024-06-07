/*
Exemplo básico de ESP8266 MQTT
 Este esboço demonstra os recursos da biblioteca pubsub em combinação
 com a placa / biblioteca ESP8266.
 Ele se conecta a um servidor MQTT e:
  - publica "hello world" no tópico "outTopic" a cada dois segundos
  - inscreve-se no tópico "inTopic", imprimindo todas as mensagens
    ele recebe. NB - assume que os payloads recebidos são strings, não binários
  - Se o primeiro caractere do tópico "inTopic" for 1, LIGUE o Led ESP,
    senão desligue-o
 Ele se reconectará ao servidor se a conexão for perdida por meio de um bloqueio
 função de reconexão. Veja o exemplo 'mqtt_reconnect_nonblocking' para saber como
 obter o mesmo resultado sem bloquear o loop principal.
 Para instalar a placa ESP8266, (usando Arduino 1.6.4+):
  - Adicione o seguinte gerenciador de placa de terceiros em "Arquivo -> Preferências -> URLs de gerenciador de placas adicionais":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Abra "Ferramentas -> Placa -> Gerenciador de Placa" e clique em instalar para o ESP8266 "
  - Selecione o seu ESP8266 em "Ferramentas -> Placa"
  */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Atualize-os com valores adequados para sua rede.

const char* ssid = "Luana2";
const char* password = "40224022";
const char* mqtt_server = "192.168.1.81";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // Começamos nos conectando a uma rede WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Ligue o LED se um 1 foi recebido como primeiro caractere
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Ligue o LED (Observe que BAIXO é o nível de tensão
    // mas na verdade o LED está aceso; isto é porque
    // está ativo baixo no ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Desligue o LED tornando a tensão ALTA
  }

}

void reconnect() {
  // Faça um loop até que estejamos reconectados
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Crie um ID de cliente aleatório
    String clientId = "Homeassistant";
    clientId += String(random(0xffff), HEX);
    // Tentativa de conexão
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Depois de conectado, publique um anúncio ...
      client.publish("home/alarm", "armed_away");
      // ... e assinar novamente
      client.subscribe("home/alarm");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Aguarde 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Inicialize o pino BUILTIN_LED como uma saída
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}
