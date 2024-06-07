//TRANSMISSOR
#include <esp_now.h>
#include <WiFi.h>
// SUBSTITUA PELO SEU MAC address DO RECEPTOR
uint8_t receiverMacAddress[] = {0xAC, 0x67, 0xB2, 0x36, 0x7F, 0x28}; //AC:67:B2:36:7F:28
struct PacketData
{
  byte rx1AxisValue;//1 potenciometro para servo
  byte ry1AxisValue;//2 potenciometro para servo
  byte rx2AxisValue;//3 potenciometro para servo
  byte ry2AxisValue;//4 potenciometro para servo
  byte switch1Value;//5 chave para led
  byte switch2Value;//6 chave para led
  byte switch3Value;//7 chave para led
  byte switch4Value;//8 chave para led
  byte switch5Value;//9 chave para led
  byte switch6Value;//10 chave para led
  byte switch7Value;//11 chave para led
  byte switch8Value;//12 chave para led
};
PacketData data;
//Esta função é usada para mapear o valor do joystick de 0-4095 para 0-254. portanto, 127 é o valor central que enviamos.
//Também ajusta a banda morta no joystick.
//Os valores do Jotstick variam de 0-4095. Mas seu valor central nem sempre é 2047. É um pouco diferente.
//Então, precisamos adicionar alguma banda morta ao valor central. no nosso caso 1800-2200. Qualquer valor neste intervalo de banda morta é mapeado para o centro 127.
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
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Mensagem enviada" : "Falha na mensagem");
}
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Erro na inicialização do ESP-NOW");
    return;
  }
  else
  {
    Serial.println("Sucesso: ESP-NOW Inicializado");
  }
  esp_now_register_send_cb(OnDataSent);

  // Registrar par
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Adicionar par
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Falha ao adicionar o par");
    return;
  }
  else
  {
    Serial.println("Successo: Adicionado par");
  }
  pinMode(15, INPUT_PULLUP);//5
  pinMode(16, INPUT_PULLUP);//6
  pinMode(17, INPUT_PULLUP);//7
  pinMode(18, INPUT_PULLUP);//8
  pinMode(19, INPUT_PULLUP);//9
  pinMode(21, INPUT_PULLUP);//10
  pinMode(22, INPUT_PULLUP);//11
  pinMode(23, INPUT_PULLUP);//12
}
void loop()
{
  data.rx1AxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(32), false);//1
  data.ry1AxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(33), false);//2
  data.rx2AxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(34), false);//3
  data.ry2AxisValue    = mapAndAdjustJoystickDeadBandValues(analogRead(35), false);//4
  data.switch1Value   = !digitalRead(15);//5
  data.switch2Value   = !digitalRead(16);//6
  data.switch3Value   = !digitalRead(17);//7
  data.switch4Value   = !digitalRead(18);//8
  data.switch5Value   = !digitalRead(19);//9
  data.switch6Value   = !digitalRead(21);//10
  data.switch7Value   = !digitalRead(22);//11
  data.switch8Value   = !digitalRead(23);//12
  esp_err_t result = esp_now_send(receiverMacAddress, (uint8_t *) &data, sizeof(data));
  if (result == ESP_OK)
  {
    Serial.println("Enviado com sucesso");
  }
  else
  {
    Serial.println("Erro ao enviar dado");
  }
  delay(50);
}
