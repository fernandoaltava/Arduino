

#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ESP8266mDNS.h>
//#include<ESP8266HTTPUpdateServer.h>

#define HOSTNAME "garagem" ///< Hostname. The setup function adds the Chip ID at the end.
void setup() {
  Serial.begin(115200);
  delay(100);
  String hostname(HOSTNAME);

    WiFi.mode(WIFI_STA);
    delay(10);
    WiFi.begin();
  delay(10);

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    delay(10);
  }
  Serial.println("O servico de atualizacao remota (OTA) Foi iniciado com sucesso! Abra http://");
  Serial.print(hostname);
  Serial.println(".local/update no seu browser para iniciar a atualizacao\n");

    ArduinoOTA.setHostname((const char *)hostname.c_str());

  Serial.print(hostname.c_str());
 Serial.println("123");
  ArduinoOTA.begin();
}
void loop() {
  ArduinoOTA.handle();
}
