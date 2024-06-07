#define BLYNK_PRINT Serial
#define pinPIR D5
#define sirene D3
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
bool pinValuev0 = 0;
bool alarme = 0;
bool dispara = 0;
int flag = 0;
char auth[] = "nEgAFN5Xdzi4LaQkF6piQhVk1FtuAbui";//"3-dcGdCfdG4JV4S2PsMFsjloIn3E9Zze";
char ssid[] = "Luana";
char pass[] = "40224022";
//////////////////////////////////////////////////////////////////
//WidgetLED led(V1);
//////////////////////////////////////////////////////////////////
BlynkTimer timer;
//////////////////////////////////////////////////////////////////
void notifyOnFire() {
  int isButtonPressed = digitalRead(pinPIR);
  if (isButtonPressed == 1 && flag == 0 && alarme == 1) {
    Serial.println("Alarme acionado");
    Blynk.notify("Alerta : invasão de perimetro");
    flag = 1;
    dispara = 1;
    tocaSirene();
  }
  else if (isButtonPressed == 0) {
    flag = 0;
    dispara = 0;
  }
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
BLYNK_WRITE(V0) {
  Blynk.syncAll();
  pinValuev0 = param.asInt();
  if (pinValuev0 == 1) {
    alarme = 1;
    Serial.println("Alarme armado");
  } else {
    alarme = 0;
    Serial.println("Alarme desarmado");
  }
}
//////////////////////////////////////////////////////////////////
void tocaSirene()
{
   Blynk.write(D0, 1);
  Blynk.virtualWrite(D3, HIGH);
  digitalWrite(sirene, HIGH);
  //led.on();
  delay(5000);
   Blynk.write(D0, 0);
  Blynk.virtualWrite(D3, LOW);
  digitalWrite(sirene, LOW);
  //led.off();
}
//////////////////////////////////////////////////////////////////
////BLYNK_READ(V2) {
  //  if (alarme == 1 && dispara == 1) {
  //    Serial.println("Alarme disparado");
  //  } else {
  //    Serial.println("Alarme rearmado");
  //  }
////  Blynk.virtualWrite(V2, millis() / 1000);
////  Blynk.virtualWrite(sirene, 1);
//  digitalWrite(sirene, HIGH);
////  delay(100);
////    Blynk.virtualWrite(sirene, 0);
//digitalWrite(sirene, LOW);
////}
//////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(pinPIR, INPUT);
  timer.setInterval(100L, notifyOnFire);
  pinMode(sirene, OUTPUT);
}
//////////////////////////////////////////////////////////////////
void loop() {
  Blynk.run();
  timer.run();
}
