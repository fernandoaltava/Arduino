#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
// WiFi connect timeout per AP. Increase when connecting takes longer.
const uint32_t connectTimeoutMs = 5000;
void setup() {
//  pinMode (d4,OUTPUT);
//  digitalWrite
  // Don't save WiFi configuration in flash - optional
  WiFi.persistent(false);
  Serial.begin(115200);
  Serial.println("\nESP8266 Multi WiFi example");
  // Set WiFi to station mode
  WiFi.mode(WIFI_STA);
  // Register multi WiFi networks
  wifiMulti.addAP("Recanto Reencontro", "40224022");
  //wifiMulti.addAP("Luana", "40224022");
  wifiMulti.addAP("Luana1", "40224022");
  wifiMulti.addAP("Luana2", "40224022");
  wifiMulti.addAP("Belao", "12345678901234567890");
  wifiMulti.addAP("GalaxyA30sAltava", "altava2018");
  // More is possible
}
void loop() {
  // Maintain WiFi connection
  if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED) {
    Serial.print("WiFi connected: ");
    Serial.print(WiFi.SSID());
    Serial.print(" ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi not connected!");
  }
  delay(1000);
}
