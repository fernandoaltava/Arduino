/*////////Shield Padawan////////////////
Botão D2 IN
LED RGB vermelho D5 verde D3 azul D6 OUT 
Potenciometro A2 IN
Sensor temp lm35 A0 IN
LDR A1 IN
Saida geral D9 OUT
LEDs verde D8 amarelo1 D7 amarelo2 A5 vermelho A4 OUT
Display D3 D5 D6 D7 D8 A4 A5 OUT
Seleção A3 OUT 0 display 1 leds
*/
#include <Pino.h>

Pino led1(5);
Pino led2(6);
Pino led3(3);
Pino led4(A3);//pino a3 seletor padawan
void setup() {
  // Serial.begin(115200);
  pinMode(2, INPUT);
}
void loop() {
  bool bot = digitalRead(2);
  if (bot > 0) {
    //led4.desligar();
    led1.pulsoA(100, 100);
  }
  else {
    //led4.ligar();
    led2.pulsoA(100, 100);
  }
  //  led3.pulsoB(50, 10);
  //  led4.piscar(10);
}
