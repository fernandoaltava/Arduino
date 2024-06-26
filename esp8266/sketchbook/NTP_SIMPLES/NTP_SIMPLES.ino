#include "NTPClient.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
const char *ssid = "Luana2";
const char *password = "40224022";
const long utcOffsetInSeconds = -10800;
char daysOfTheWeek[7][12] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
void setup(){
Serial.begin(115200);
WiFi.begin(ssid, password);
while ( WiFi.status() != WL_CONNECTED ) {
delay ( 500 );
Serial.print ( "." );
}
timeClient.begin();
}

void loop() {
timeClient.update();
Serial.print(daysOfTheWeek[timeClient.getDay()]);
Serial.print(" ");
Serial.println(timeClient.getFormattedTime());
delay(1000);
}
