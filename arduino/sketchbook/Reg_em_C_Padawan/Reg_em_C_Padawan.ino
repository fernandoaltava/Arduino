extern volatile unsigned long timer0_millis;//variavel para zerar o millis

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PADAWAN.h"
/////////////////////////////////////
void setup() {
  //Serial.begin(9600);
  SetBit(regiA3, bitiA3); //DDRC , PC3); //pino A3 como saída. registrador de direção
  SetBit(portA3, bitiA3); //PORTC, PC3); //coloca pino A3 em HIGH registrador de saida
  ClrBit(regiA2, bitiA2); //DDRC , PC2); //pino A2 como entrada registrador de direção
  ClrBit(regiA1, bitiA1); //DDRC , PC1); //pino A1 como entrada registrador de direção
  ClrBit(regiD2, bitiD2); //DDRD , PD2); //pino d2 como entrada registrador de direção
  SetBit(regiD7, bitiD7); //DDRD , PD3); //Pino d7 como saída. registrador de direção
  SetBit(regiD5, bitiD5);//registrador de direção
  SetBit(regiD6, bitiD6);//registrador de direção
}
/////////////////////////////////////
void loop() {
  while (TstBit(PIND, bitiD2)) {
    ClrBit(portD5, bitiD5);//registrador de saida
    ClrBit(portD6, bitiD6);//registrador de saida
    CplBit(portD3, bitiD3);//registrador de saida
    _delay_ms( 50 );
  }
    while (analogRead(A1)<100) {
    ClrBit(portD5, bitiD5);//registrador de saida
    ClrBit(portD3, bitiD3);//registrador de saida
    CplBit(portD6, bitiD6);//registrador de saida
    _delay_ms( 50 );
  }
  //
  //ClrBit(portD3, bitD3);//registrador de saida
  //Serial.println(analogRead(A1));// + " " + analogRead(A1));
  _delay_ms( 50 );

  if (analogRead(A2) > 148) {
    ClrBit(portD3, bitiD3);//registrador de saida
    ClrBit(portD6, bitiD6);//registrador de saida
    CplBit(portD5, bitiD5);//registrador de saida vermelho
  }
  if (analogRead(A2) <= 148 and analogRead(A2) > 75 ) {
    ClrBit(portD3, bitiD3);//registrador de saida
    ClrBit(portD5, bitiD5);//registrador de saida
    CplBit(portD6, bitiD6);//registrador de saida azul
  }
  if (analogRead(A2) <= 75) {
    ClrBit(portD5, bitiD5);//registrador de saida
    ClrBit(portD6, bitiD6);//registrador de saida azul
    CplBit(portD3, bitiD3);
  }

//Zera o millis
if (millis()>= 4316400000){//valor dos 50 dias menos 1 hora
noInterrupts();
timer0_millis = 0;
interrupts();
}

}
/////////////////////////////////////
