#include <neotimer.h>
Neotimer  tempo1 = Neotimer(150);
Neotimer  tempo2 = Neotimer(2500);
void teste();
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (tempo1.repeat())
  {
    digitalWrite(13, !digitalRead(13));
    Serial.println("teste1");
  }

  if (tempo2.repeat())
  {
       Serial.println("teste2");
    teste();
    Serial.println("teste2,5");
  }
}
void teste() {
  for (int a = 0; a < 1000; a++) {
    Serial.println(a);
  }


}
