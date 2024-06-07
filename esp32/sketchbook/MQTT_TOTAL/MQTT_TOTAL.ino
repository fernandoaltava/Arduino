#include <FS.h>
#include <WiFiManager.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
const uint32_t connectTimeoutMs = 5000;

void setup() {
  WiFi.persistent(false);
  Serial.begin(115200);
  Serial.println("\nESP8266 Multi WiFi example");
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP("Recanto Reencontro", "40224022");
  wifiMulti.addAP("Luana", "40224022");

  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECT_FAILED){//WL_CONNECTED) {
    Serial.print("WiFi conectado 1: ");
    Serial.print(WiFi.SSID());
    Serial.print(" ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("WiFi não conectado!");
    WiFiManager wifiManager;
    wifiManager.setBreakAfterConfig(true);

    if (!wifiManager.autoConnect("AutoConnectAP", "password")) {
      Serial.println("falha na conexão, reset agora");
      delay(3000);
      ESP.restart();
      delay(5000);
    }
  }
  //Serial.println("conectado...yeey :)");
  //Serial.print("local ip  ");
  //Serial.println(WiFi.localIP());
}
void loop() {
  delay(1000);
  Serial.print("WiFi conectado 2: ");
  Serial.print(WiFi.SSID());
  Serial.print(" ");
  Serial.println(WiFi.localIP());

}
