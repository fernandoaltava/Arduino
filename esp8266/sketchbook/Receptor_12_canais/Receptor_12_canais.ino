//RECEPTOR
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>
#define SIGNAL_TIMEOUT 1000  // Este é o tempo limite do sinal em milissegundos. Vamos redefinir os dados se não houver sinal
unsigned long lastRecvTime = 0;
struct PacketData
{
  byte rx1AxisValue;//1 servo
  byte ry1AxisValue;//2 servo
  byte rx2AxisValue;//3 servo
  byte ry2AxisValue;//4 servo
  byte switch1Value;//5 led
  byte switch2Value;//6 led
  byte switch3Value;//7 led
  byte switch4Value;//8 led  
  byte switch5Value;//9 led
  byte switch6Value;//10 led
  byte switch7Value;//11 led
  byte switch8Value;//12 led  
};
PacketData receiverData;
Servo servo1;//1     
Servo servo2;//2     
Servo servo3;//3     
Servo servo4;//4     
int   led1 = 15;//5
int   led2 = 16;//6
int   led3 = 17;//7
int   led4 = 18;//8
int   led5 = 19;//9
int   led6 = 21;//10
int   led7 = 22;//11
int   led8 = 23;//12
//Atribuir valores recebidos de entrada padrão
void setInputDefaultValues()
{
  // A posição do meio para joystick. (254/2=127)
  receiverData.rx1AxisValue = 127;//1
  receiverData.ry1AxisValue = 127;//2
  receiverData.rx2AxisValue = 127;//3
  receiverData.ry2AxisValue = 127;//4
  receiverData.switch1Value = LOW;//5
  receiverData.switch2Value = LOW;//6
  receiverData.switch3Value = LOW;//7
  receiverData.switch4Value = LOW;//8
  receiverData.switch5Value = LOW;//9
  receiverData.switch6Value = LOW;//10
  receiverData.switch7Value = LOW;//11
  receiverData.switch8Value = LOW;//12   
}
void mapAndWriteValues()
{
  servo1.write(map(receiverData.rx1AxisValue, 0, 254, 0, 180));//1
  servo2.write(map(receiverData.ry1AxisValue, 0, 254, 0, 180));//2
  servo3.write(map(receiverData.rx2AxisValue, 0, 254, 0, 180));//3
  servo4.write(map(receiverData.ry2AxisValue, 0, 254, 0, 180));//4
  digitalWrite(led1, receiverData.switch1Value);//5
  digitalWrite(led2, receiverData.switch2Value);//6
  digitalWrite(led3, receiverData.switch3Value);//7
  digitalWrite(led4, receiverData.switch4Value);//8 
  digitalWrite(led5, receiverData.switch5Value);//9
  digitalWrite(led6, receiverData.switch6Value);//10
  digitalWrite(led7, receiverData.switch7Value);//11
  digitalWrite(led8, receiverData.switch8Value);//12   
}
// função de retorno de chamada que será executada quando os dados forem recebidos
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  if (len == 0)
  {
    return;
  }
  memcpy(&receiverData, incomingData, sizeof(receiverData));
  mapAndWriteValues();  
  lastRecvTime = millis(); 
}
void setUpPinModes()
{
  servo1.attach(27);//1
  servo2.attach(26);//2
  servo3.attach(25);//3
  servo4.attach(33);//4
  pinMode(led1, OUTPUT);//5
  pinMode(led2, OUTPUT);//6
  pinMode(led3, OUTPUT);//7
  pinMode(led4, OUTPUT);//8      
  pinMode(led5, OUTPUT);//9
  pinMode(led6, OUTPUT);//10
  pinMode(led7, OUTPUT);//11
  pinMode(led8, OUTPUT);//12
  setInputDefaultValues();
  mapAndWriteValues();
}
void setup() 
{
  setUpPinModes();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}
void loop()
{
  //Verifique o sinal perdido.
  unsigned long now = millis();
  if ( now - lastRecvTime > SIGNAL_TIMEOUT ) 
  {
    setInputDefaultValues();
    mapAndWriteValues();  
  }
}
