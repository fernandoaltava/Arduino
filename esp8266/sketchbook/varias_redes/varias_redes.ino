#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>
const char *ssid1 = "Luana2";
const char *password1 = "40224022";
const char *ssid2 = "Recanto Reencontro";
const char *password2 = "40224022";
const char *ssid3 = "Luana2";
const char *password3 = "40224022";
int flag;
const IPAddress remote_ip(8, 8, 8, 8);

void minhaRede();

void setup() {
  Serial.begin(115200);
  while (WiFi.status() == WL_DISCONNECTED) {
    minhaRede();
  }
  Serial.println("Conectado");
}

void loop() {
  if (!Ping.ping(remote_ip)) {
    Serial.println("Sem Internet");
    minhaRede();
  } else {
    Serial.println("Internet conectada");
    Serial.print("Conectado a:  ");
    Serial.println(WiFi.SSID());              // Diga-nos a qual rede estamos conectados
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }
}


void minhaRede() {
  int flag = 1;
  Serial.println("Procurando rede .....");
  int rede = WiFi.scanNetworks();
  for (int i = 0; i < rede; i++) {
    switch (flag) {
      case 1:
        flag = 2;
        if (WiFi.SSID(i) == ssid1) {
          WiFi.begin(ssid1, password1);
          Serial.println("/n Wifi encontrada");
          delay(2000);
          Serial.println("Conectando, aguarde  ");
          delay(2000);
        }
      case 2:
        flag = 3;
        if (WiFi.SSID(i) == ssid2) {
          WiFi.begin(ssid2, password2);
          Serial.println("/n Wifi encontrada");
          delay(2000);
          Serial.println("Conectando, aguarde  ");
          delay(2000);
        }
      case 3:
        flag = 1;
        if (WiFi.SSID(i) == ssid3) {
          WiFi.begin(ssid3, password3);
          Serial.println("/n Wifi encontrada");
          delay(2000);
          Serial.println("Conectando, aguarde  ");
          delay(2000);
        }
    }
  }
}
