/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

float  temperatura;
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
void printDeviceAddress() {

const uint8_t* point = esp_bt_dev_get_address();

for (int i = 0; i < 6; i++) {
   char str[3];
   sprintf(str, "%02X", (int)point[i]);
   Serial.print(str);
   if (i < 5){
   Serial.print(":");}
}
Serial.println();
}

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

void setup()
{
temperatura = 0;
Serial.begin(9600);

pinMode(2, OUTPUT);
  delay(300);
  SerialBT.begin("ESP32test");
  Serial.println("Este é o seu endereço");
  printDeviceAddress();

}


void loop()
{
if(SerialBT.connect())Serial.println("conectado");
    if (SerialBT.available()) {
      digitalWrite(2,LOW);
      temperatura = ((temprature_sens_read() - 32 ) / 1.8);
      SerialBT.write(char(temperatura));
      delay(300);
      Serial.println(char(temperatura));

    }

}
