#define BLYNK_PRINT Serial
//#define garagem D0
//#define corredor D1
//#define quintal D2
//#define sirene D3
#define pinPIR D5

unsigned long agora, antes = 0;

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
int pinValuev0, pinValuev1, pinValuev2, pinValuev3, pinValuev4 = 0;
bool alarme = 0;
int flag = 0;
char auth[] = "nEgAFN5Xdzi4LaQkF6piQhVk1FtuAbui";//"3-dcGdCfdG4JV4S2PsMFsjloIn3E9Zze";
char ssid[] = "Luana";
char pass[] = "40224022";
//////////////////////////////////////////////////////////////////
BlynkTimer timer;
//////////////////////////////////////////////////////////////////
void notifyOnFire() {
  int isButtonPressed = digitalRead(pinPIR);
  if (isButtonPressed == 1 && flag == 0 && alarme == 1) {
    //Serial.println("Alarme acionado");
    Blynk.notify("Alerta : invasão de perimetro");
    flag = 1;
    //Blynk.virtualWrite(V4, 1);
    tarefa1();
    // delay(2000);
    //Blynk.virtualWrite(V4, 0);
  }
  else if (isButtonPressed == 0) {
    flag = 0;
    //Serial.println("Alarme em espera");

    //Blynk.virtualWrite(V4, 0);
  }
}
//////////////////////////////////////////////////////////////////
BLYNK_WRITE(V3) {//alarme
  pinValuev3 = param.asInt();
  if (pinValuev3 == 1) {
    alarme = 1;
  } else {
    alarme = 0;
  }
}
//////////////////////////////////////////////////////////////////
BLYNK_WRITE(V4) {//sirene
  pinValuev4 = param.asInt();
//  if (pinValuev4 == 1) {
  if ( 1) {
    Blynk.virtualWrite(V12, 255);
    //Serial.println("1");
    digitalWrite(D3, HIGH);
    //    delay(2000);
    timer.setTimeout(2000L, []() {
      Blynk.virtualWrite(V12, 0);
      digitalWrite(D3, LOW);
    });
  }
}
//////////////////////////////////////////////////////////////////
void tarefa1() {
  if ( 1) {
    Blynk.virtualWrite(V12, 255);
    //Serial.println("1");
    digitalWrite(D3, HIGH);
    //    delay(2000);
    timer.setTimeout(10000L, []() {
      Blynk.virtualWrite(V12, 0);
      digitalWrite(D3, LOW);
    });
  }
  
  
  
  
  //Serial.println("21");
////  digitalWrite(sirene, HIGH);
////  delay(20000);
  //Serial.println("20");
////  digitalWrite(sirene, LOW);
}
//////////////////////////////////////////////////////////////////
void setup() {
  //Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(pinPIR, INPUT);
  timer.setInterval(10L, notifyOnFire);
  //pinMode(sirene, OUTPUT);
}
//////////////////////////////////////////////////////////////////
void loop() {
  Blynk.run();
  timer.run();
}
