//Transceiver 1 Sketch:
//--------------------------------------------
//ESP32 Tranceiver 1 via ESP-NOW Protocol
//Transmit Pot Value - Receive Temp & Humidity
//--------------------------------------------
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//------------------------------------------------------------
Adafruit_SSD1306 display(128, 64, &Wire, -1);

//------------------------------------------------------------
uint8_t RxMACaddress[] = {0x7C, 0x9E, 0xBD, 0xF5, 0xBE, 0x30};
//------------------------------------------------------------
typedef struct TxStruct
{
  int potVal;
}TxStruct;
TxStruct sentData;
//------------------------------------------------------------
typedef struct RxStruct
{
  float temp; int humidity;
}RxStruct;
RxStruct receivedData;
//------------------------------------------------------------
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
//------------------------------------------------------------
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  
}
//======================================================================================
void setup()
{
  Serial.begin(115200);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  //----------------------------------------------------------
  WiFi.mode(WIFI_STA);
  //----------------------------------------------------------
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //----------------------------------------------------------
  esp_now_register_send_cb(OnDataSent);
  //----------------------------------------------------------
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, RxMACaddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  //----------------------------------------------------------
  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
  //----------------------------------------------------------
  esp_now_register_recv_cb(OnDataRecv);
}
//======================================================================================
void loop()
{
  sentData.potVal = analogRead(A0);
  
  //----------------------------------------------------------
  esp_err_t result = esp_now_send(RxMACaddress, (uint8_t *) &sentData, sizeof(sentData));
  //----------------------------------------------------------
  if (result == ESP_OK) Serial.println("Sent with success");
  else Serial.println("Error sending the data");
  //----------------------------------------------------------
  display.setTextColor(WHITE); display.clearDisplay();
  display.setTextSize(2); display.setCursor(0,0); display.print("--DHT 11--");
  display.setCursor(0,25); display.print("T: ");
  display.print(receivedData.temp); display.print("C");
  display.setCursor(0,50); display.print("H: ");
  display.print(receivedData.humidity); display.print("%");
  display.display();
}
