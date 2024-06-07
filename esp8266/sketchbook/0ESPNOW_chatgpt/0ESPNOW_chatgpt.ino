/*
ESP1 84:F3:EB:4E:69:71 {0x84, 0xF3, 0xEB, 0x4E, 0x69, 0x71}//
ESP2 CC:50:E3:32:A8:7D {0xCC, 0x50, 0xE3, 0x32, 0xA8, 0x7D}//
ESP3 B4:E6:2D:3E:5A:64 {0xB4, 0xE6, 0x2D, 0x3E, 0x5A, 0x64}//
esp4 E8:DB:84:B1:56:63 {0xE8, 0xDB, 0x84, 0xB1, 0x56, 0x63}//
*/
#include <ESP8266WiFi.h>
#include <espnow.h>

#define rele 0
#define botao 2
int disparado = 0;
int dado = 0;
void envia();
void dispara();

////////////////////////////////////////////////////////////////////////////
// Substitua o endereço MAC do segundo ESP8266
uint8_t mac1[] = {0x84, 0xF3, 0xEB, 0x4E, 0x69, 0x71};//{0x12, 0x34, 0x56, 0x78, 0x90, 0xAB};//Endereço MAC do RX1
uint8_t mac2[] = {0xCC, 0x50, 0xE3, 0x32, 0xA8, 0x7D};//{0x12, 0x34, 0x56, 0x78, 0x90, 0xAB};//Endereço MAC do RX2

//uint8_t mac3[] = {0xB4, 0xE6, 0x2D, 0x3E, 0x5A, 0x64};//{0x12, 0x34, 0x56, 0x78, 0x90, 0xAB};//Endereço MAC do TX1
//uint8_t mac4[] = {0xE8, 0xDB, 0x84, 0xB1, 0x56, 0x63};//{0x12, 0x34, 0x56, 0x78, 0x90, 0xAB};//Endereço MAC do TX2

////////////////////////////////////////////////////////////////////////////
// Estrutura para armazenar os dados recebidos
struct DataStruct
{
  int value;
};

////////////////////////////////////////////////////////////////////////////
// Variável para armazenar dados recebidos
DataStruct receivedData;

////////////////////////////////////////////////////////////////////////////
// Função de callback para receber dados
void onDataReceived(uint8_t *senderMac, uint8_t *data, uint8_t len)
{
  // Copiar os dados recebidos para a estrutura
  memcpy(&receivedData, data, sizeof(DataStruct));

  // Imprimir os dados recebidos
  Serial.print("Dados recebidos de: ");
  delay(2000);
  dispara();
  //for (int i = 0; i < 6; i++)
  //{
   // Serial.print(senderMac[i], HEX);
   // if (i < 5) Serial.print(":");
  //}
  //Serial.println();
  //Serial.print("Valor recebido: ");
  //Serial.println(receivedData.value);
  //if (receivedData.value > 0)dispara();
}

////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  pinMode(botao, INPUT);
  pinMode(rele, OUTPUT);
  // Inicializar ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0)
  {
    Serial.println("Erro ao inicializar ESP-NOW");
    return;
  }

  // Registrar a função de callback para receber dados
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);//SLAVE);
  esp_now_register_recv_cb(onDataReceived);

  // Adicionar o segundo ESP8266 à lista de parceiros
  esp_now_add_peer(mac1, ESP_NOW_ROLE_COMBO, 1, NULL, 0);//MASTER, 1, NULL, 0);//Parceiro RX1 adicionado
  esp_now_add_peer(mac2, ESP_NOW_ROLE_COMBO, 1, NULL, 0);//MASTER, 1, NULL, 0);//Parceiro RX2 adicionado

//  esp_now_add_peer(mac3, ESP_NOW_ROLE_COMBO, 1, NULL, 0);//MASTER, 1, NULL, 0);//Parceiro TX1 adicionado
//  esp_now_add_peer(mac4, ESP_NOW_ROLE_COMBO, 1, NULL, 0);//MASTER, 1, NULL, 0);//Parceiro TX2 adicionado

  Serial.println("Iniciando...");
  delay(2000);
}

////////////////////////////////////////////////////////////////////////////
void loop()
{
  //envia();//Nos RX desabilitar enta linha
  digitalWrite(rele, HIGH);
  delay(2000);
    Serial.println("LOOP");

}

////////////////////////////////////////////////////////////////////////////
void envia()
{
  //dado = 10;
  //Estrutura de dados 1
  dado = random(1, 20);
  DataStruct sendData1;
  sendData1.value = dado;//analogRead(A0); // Pode ser substituído por outros dados

  //Estrutura de dados 2
  dado = random(21, 40);
  DataStruct sendData2;
  sendData2.value = dado; //analogRead(A0); // Pode ser substituído por outros dados

  // Enviar dados para os parceiros
  esp_now_send(mac1, (uint8_t *)&sendData1, sizeof(DataStruct));//Envia dados (sendData1) para parceiro RX1
  esp_now_send(mac2, (uint8_t *)&sendData2, sizeof(DataStruct));//Envia dados (sendData2) para parceiro RX2

//  esp_now_send(mac3, (uint8_t *)&sendData1, sizeof(DataStruct));//Envia dados (sendData1) para parceiro TX1
//  esp_now_send(mac4, (uint8_t *)&sendData2, sizeof(DataStruct));//Envia dados (sendData2) para parceiro TX2
}

////////////////////////////////////////////////////////////////////////////
void dispara()
{
  //tempo1.restart();
  for(int conta=0;conta<10;conta++) //
  {
      Serial.println(conta);

    digitalWrite(rele, !digitalRead(rele));
    delay(500);
  }
} 
