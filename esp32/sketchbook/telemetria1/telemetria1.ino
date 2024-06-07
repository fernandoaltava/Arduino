//Temperatura
//ventoinha 1
//ventoinha 2
//pressão de oleo
//bateria
//combustivel

//ignição
//arranque
//ventoinha 1
//ventoinha 2
//saida b
//saida B
//saida c
//saida C
//saida d
//saida D



#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

// Verifique se as configurações do Bluetooth estão ativadas
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth não está habilitado! Por favor, execute `make menuconfig` e habilite-o
#endif
float um, dois, tres, quatro, cinco, seis, sete, oito, nove, dez = 0;

float  temperatura;
#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();//sensor de temperatura interna

// Objeto Bluetooth Serial
BluetoothSerial SerialBT;

//void printDeviceAddress() {
//  const uint8_t* point = esp_bt_dev_get_address();
//  for (int i = 0; i < 6; i++) {
//    char str[3];
//    sprintf(str, "%02X", (int)point[i]);
//    Serial.print(str);
//    if (i < 5) {
//      Serial.print(":");
//    }
//  }
//  Serial.println();
//}

const int ledPin =  2;

// Lidar com mensagens recebidas e enviadas
String message = "";
char incomingChar;
String temperatureString = "";
// Timer: auxiliar variables
unsigned long previousMillis = 0;    // Armazena a última vez que a temperatura foi publicada
const long interval = 500;         // intervalo no qual publicar as leituras do sensor
void dadosBluetooth();
void arranque();
void ventoinha1();
void ventoinha2();


void setup() {
  //temperatureString = ((temprature_sens_read() - 32 ) / 1.8);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  //printDeviceAddress();
  // Bluetooth device name
  SerialBT.begin("ESP32");
  Serial.println("O dispositivo foi iniciado, agora você pode emparelhá-lo com bluetooth!");
}

void loop() {
  if (SerialBT.connected()) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  um = (touchRead(T3));  //analogRead(36);
  dois = analogRead(39);
  tres = analogRead(34);
  quatro = analogRead(35);
  cinco = analogRead(32);
  seis = analogRead(33);
  sete = analogRead(25);
  oito = analogRead(26);
  nove = analogRead(27);
  dez = analogRead(14);
  dadosBluetooth();

}
///////////////////////////////////////////////////////////
void dadosBluetooth() {
  unsigned long currentMillis = millis();
  // Envia parametros
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    temperatureString = ((temprature_sens_read() - 32 ) / 1.8);
    SerialBT.print(um);
    SerialBT.print(";");
    SerialBT.print(dois);
    SerialBT.print(";");
    SerialBT.print(tres);
    SerialBT.print(";");
    SerialBT.print(quatro);
    SerialBT.print(";");
    SerialBT.print(cinco);
    SerialBT.print(";");
    SerialBT.print(seis);
    SerialBT.print(";");
    SerialBT.print(sete);
    SerialBT.print(";");
    SerialBT.print(oito);
    SerialBT.print(";");
    SerialBT.print(nove);
    SerialBT.print(";");
    SerialBT.print(dez);//temperatureString);//dez);
    SerialBT.println(";");
  }
  // Recebe dados
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n') {
      message += String(incomingChar);

      switch (incomingChar) {
        case 'A':
          Serial.println("Motor de arranque acionado");
          arranque();
          break;
        case 'v':
          Serial.println("Ventoinha 1 acionada");
          ventoinha1();
          break;
        case 'V':
          Serial.println("Ventoinhas acionadas");
          ventoinha2();
          break;
        case 'B':
          Serial.println("BBBBBBB");
          //ventoinha2();
          break;
        case 'b':
          Serial.println("bbbbbbbb");
          //ventoinha2();
          break;
        case 'C':
          Serial.println("CCCCCCCC");
          //ventoinha2();
          break;
        case 'c':
          Serial.println("cccccccc");
          //ventoinha2();
          break;
        case 'D':
          Serial.println("DDDDDDDD");
          //ventoinha2();
          break;
        case 'd':
          Serial.println("dddddddd");
          //ventoinha2();
          break;
      }
    }
  }
}
///////////////////////////////////////////////////////////
void arranque() {
  if (digitalRead(2) == HIGH) {
    Serial.println("Acionando o arranque");
  }
}
///////////////////////////////////////////////////////////
void ventoinha1() {
  if (digitalRead(2) == HIGH) {
    Serial.println("Acionando o ventoinha 1");
  }
}
///////////////////////////////////////////////////////////
void ventoinha2() {
  if (digitalRead(2) == HIGH) {
    Serial.println("Acionando o ventoinha 2");
  }
}
///////////////////////////////////////////////////////////
