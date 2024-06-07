#include <esp_now.h>
#include <WiFi.h>
// SUBSTITUA PELO SEU ENDEREÇO MAC DO RECEPTOR
uint8_t receiverMacAddress[] = {0x3C,0x71,0xBF,0xF1,0x61,0x78};  //AC:67:B2:36:7F:28
                                //3C:  71:  BF:  F1:  61:  78
struct PacketData
{
  byte lxAxisValue;
  byte lyAxisValue;
  byte rxAxisValue;
  byte ryAxisValue;
 
  byte switch1Value;
  byte switch2Value;
  byte switch3Value;
  byte switch4Value;  
  byte switch5Value;
  byte switch6Value;
  byte switch7Value;
  byte switch8Value;  
};
PacketData data;

//Esta função é usada para mapear o valor do joystick 0-4095 para 0-254. portanto, 127 é o valor central que enviamos.
//Também ajusta a zona morta no joystick.
//Os valores do Jotstick variam de 0 a 4095. Mas o seu valor central nem sempre é 2047. É um pouco diferente.
//Portanto, precisamos adicionar alguma zona morta ao valor central. no nosso caso, 1800-2200. Qualquer valor nesta faixa de zona morta é mapeado para o centro 127.
int mapAndAdjustJoystickDeadBandValues(int value, bool reverse)
{
  if (value >= 2200)
  {
    value = map(value, 2200, 4095, 127, 254);
  }
  else if (value <= 1800)
  {
    value = (value == 0 ? 0 : map(value, 1800, 0, 127, 0));  
  }
  else
  {
    value = 127;
  }

  if (reverse)
  {
    value = 254 - value;
  }
  Serial.println(value);  
  return value;
}

// retorno de chamada quando os dados são enviados
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nStatus de envio do último pacote:\t ");
  Serial.println(status);
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Mensagem enviada" : "Mensagem falhou");
}

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Iniciando ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Erro na inicialização do ESP-NOW");
    return;
  }
  else
  {
    Serial.println("Sucesso: ESP-NOW inicializado");
  }

  esp_now_register_send_cb(OnDataSent);
  
  // Registra o par
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMacAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Adiciona o par        
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Falha na adição do par");
    return;
  }
  else
  {
    Serial.println("Sucesso: Par adicionado");
  } 

  pinMode(15,INPUT_PULLUP);
  pinMode(16,INPUT_PULLUP);
  pinMode(17,INPUT_PULLUP);
  pinMode(18,INPUT_PULLUP); 
  pinMode(19,INPUT_PULLUP);
  pinMode(21,INPUT_PULLUP);
  pinMode(22,INPUT_PULLUP);
  pinMode(23,INPUT_PULLUP); 
     
}
 
void loop() 
{
  data.lxAxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(32), false);
  data.lyAxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(33), false);
  data.rxAxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(34), false);
  data.ryAxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(35), false);
  data.switch1Value   = !digitalRead(15);
  data.switch2Value   = !digitalRead(16);
  data.switch3Value   = !digitalRead(17);
  data.switch4Value   = !digitalRead(18);
  data.switch5Value   = !digitalRead(19);
  data.switch6Value   = !digitalRead(21);
  data.switch7Value   = !digitalRead(22);
  data.switch8Value   = !digitalRead(23);  
  
  esp_err_t result = esp_now_send(receiverMacAddress, (uint8_t *) &data, sizeof(data));
  if (result == ESP_OK) 
  {
    Serial.println("Enviado com sucesso");
  }
  else 
  {
    Serial.println("Erro ao enviar os dados");
  }    
  
  delay(50);
}
