//Arduino UNO
//PORTB: PB0 a PB5 (8 a 13)
//PORTC: PC0 a PC5 (A0 a A5)
//PORTD: PD0 a PD7 (0 a 7)
//pino 7 é PD7   DDRD |=(1 << DDD7); igual a  pinMode(7, OUTPUT);
//pino 13 é PB5  DDRB |=(1 << DDB5);
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SetBit(RES, BIT)(RES |= (1 << BIT))   // Por BIT em nível alto
#define ClrBit(RES, BIT)(RES &= ~ (1 << BIT)) // Por BIT em nível baixo
#define TstBit(RES, BIT)(RES &  (1 << BIT)) // testar BIT, retorna 0 ou 1
#define CplBit(RES, BIT)(RES ^= (1 << BIT)) // Inverter estado do BIT

int main() {
  // BIT 76543210
  SetBit(DDRC, PC3);
  SetBit(PORTC, PC3);  
  SetBit(DDRD, PD7);  //Pino 13 como saída.
  while ( true ) {
//    ClrBit(PORTB, PB5); // bit PB5 LOM
//    _delay_ms( 500 );
//    SetBit(PORTB, PB5); // bit PB5 HIGH
//    _delay_ms( 500 );

    CplBit(PORTD, PD7);
    _delay_ms( 500 );


  }
  return 0;
}
