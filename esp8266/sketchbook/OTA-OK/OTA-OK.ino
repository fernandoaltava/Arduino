#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
#define HOSTNAME "garagem" ///< Hostname. The setup function adds the Chip ID at the end.
void setup() {
  Serial.begin(115200);
  delay(100);
  //String hostname(HOSTNAME);
  WiFi.mode(WIFI_STA);
  delay(10);
  WiFi.begin("Luana","40224022");
  delay(100);
    while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("IP address: não ");
    Serial.println(WiFi.localIP());
    delay(10);
  }

  //ArduinoOTA.setHostname((const char *)hostname.c_str());
  Serial.print("Hostname   ");
//  Serial.println(Hostname.c_str());
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
}
