#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <neotimer.h>
Neotimer  tempo1 = Neotimer(500);
Neotimer  tempo2 = Neotimer(20000);

void setup() {
  Serial.begin(9600);
  // Serial.println();
  //Serial.print("ESP Board MAC Address:  ");
  //Serial.println(WiFi.macAddress());
}

void loop() {
  if (tempo1.repeat())
  {
    Serial.println();
    Serial.print("ESP Board MAC Address:  ");
    Serial.println(WiFi.macAddress());
    //delay(1000);
  }
//  if (tempo2.repeat())
 // {
 //   tempo1.restart ();
 // }

}
