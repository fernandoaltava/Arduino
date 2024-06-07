#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
const char* ssid     = "Recanto Reencontro";
const char* password = "40224022";
//const IPAddress remote_ip(192, 168, 0, 1);
const char* remote_host = "150.136.173.206";
void setup() {
  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected with ip ");
  Serial.println(WiFi.localIP());
  Serial.print("Pinging ip ");
  Serial.println(remote_host);
}
void loop() {
  if (Ping.ping(remote_host)) {
    Serial.println("Success!!");
  } else {
    Serial.println("Error :(");
  }
  delay(500);
}
