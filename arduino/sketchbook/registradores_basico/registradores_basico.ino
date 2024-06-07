//extern volatile unsigned long timer0_millis;//variavel para zerar o millis

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PADAWAN.h"
/////////////////////////////////////
//const byte LED = (1 << 3); // Conectado no pino 3 (bit 3 da Porta D)
//const byte BOT = (1 << 2); // Concetado no pino 12 (bit 4 da Porta B)
class Pino {
  public:
    int pino;
    int Regi, Bit, Port, regi, biti, port;
    bool mode;
    //#define regiD5 DDRD
    //#define bitiD5 PD5
    //#define portD5 PORTD

    Pino(int pin, int mode, int regi, char biti, char port) {
      pino = pin;
      if (regi == regiD5) Regi = DDRD;
      if (biti == bitiD5) Bit = PD5;
      if (port == portD5) Port = PORTD;
      //  if (mode > 0) {
      //    SetBit(regiD5, Bit);
      //  }
      if (Port == port) {
//        SetBit(regiD5, Bit);
//        SetBit(portD5, Bit);
        SetBit(regiD5, Bit);
        SetBit(portD5, Bit);
      }

    }
    void Inverter() {//metodo inverter
      CplBit(portD3, Bit);
    }
    //-------------------------------------------//

};
Pino led(5, 1, regiD5, bitiD5, portD5);
void setup() {
  Serial.begin(9600);
  //DDRD |= LED; // Configura O pino 3 como OUTPUT (1)
  //DDRD &= ~BOT; // Configura o pino 12 como INPUT (0)
  //PORTD |= BOT; // Habilita o pullup interno (1) (INPUT_PULLUP)

  //while (1) {
  //if ((PIND & BOT)) {
  //PORTD ^= LED;
  //while (!(PIND &BOT))  { }
  //delay(100);
  //}
  //PORTD &= ~LED;
}
void loop() {
  //Serial.println(port);
  //led.Inverter();
  //delay(100);
}
/*
  //Zera o millis
  if (millis()>= 4316400000){//valor dos 50 dias menos 1 hora
  noInterrupts();
  timer0_millis = 0;
  interrupts();
  }
*/
