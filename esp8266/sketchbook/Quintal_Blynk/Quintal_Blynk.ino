#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define pinPIR D5
#define sirene D2
bool pinValuev0 = 0;
bool alarme = 0;
bool dispara = 0;
int flag = 0;
char auth[] = "gP1FE6S3MrYcLD8Zn3CFT3ZdTUbypium";
char garagem[] = "GybWE5t2ieE-5cMTs0OS15y3tSAJIAuw";
char ssid[] = "Luana";
char pass[] = "40224022";
WidgetBridge bridge1(V1);

BLYNK_CONNECTED() {
  bridge1.setAuthToken("GybWE5t2ieE-5cMTs0OS15y3tSAJIAuw");
}
BlynkTimer timer;
//////////////////////////////////////////////////////////////////
void notifyOnFire() {
  int isButtonPressed = digitalRead(pinPIR);
  if (isButtonPressed == 1 && flag == 0 && alarme == 1) {
//    Serial.println("Alarme acionado");
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
  } else {
    alarme = 0;
  }
}
//////////////////////////////////////////////////////////////////
void tocaSirene()
{
  bridge1.digitalWrite(D2, HIGH);
  delay(20000);
  bridge1.digitalWrite(D2, LOW);
}
//////////////////////////////////////////////////////////////////
void setup()
{
//  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(pinPIR, INPUT);
  timer.setInterval(100L, notifyOnFire);
  pinMode(sirene, OUTPUT);
}
//////////////////////////////////////////////////////////////////
void loop()
{
  Blynk.run();
  timer.run();
}
