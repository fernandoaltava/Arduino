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

void setup() {
  ////  DDRB |= (1 << DDB5); //pino PB5 13 Saída
  ClrBit(DDRD, PD2);//pino d2 como entrada
  SetBit(DDRD, PD7);  //Pino 7 como saída.
  Serial.begin(9600);
  //  pinMode(7,OUTPUT);  //pino 13 Saída
  pinMode(A3, OUTPUT);
  //  pinMode(2,INPUT);
  digitalWrite(A3, HIGH);
}
void loop() {
  ////PORTB |= (1 << PB5); //nivel alto(liga led)
  if (TstBit(PIND, PD2) == false) {
    digitalWrite(7, HIGH); //nivel alto(liga led)
    delay(500);
    ////PORTB &= ~ (1 << PB5); //nivel baixo(desliga led)
    digitalWrite(7, LOW); //nivel baixo(desliga led)
    delay(500);
  }
  Serial.println(digitalRead(2));
  Serial.println(TstBit(PIND,PD2));


}
