////////////           Shield Padawan        /////////////
//          |-------------------------------|
//          |     UNO        Led interno  13| PB5++DDRB
//          |                             12| PB4++DDRB
//          |3.3V                         11| PB3++DDRB
//          |5V                           10| PB2++DDRB
//          |GND              Entrada     09| PB1++DDRB
//          |GND              Disp/ledVD  08| PB0++DDRB
//          |VIN                            |
//          |                 Disp/ledAM1 07| PD7--DDRD
//          |                 LEDB/Disp   06| PD6--DDRD
// DDRC PC0 |A0 LM35          LEDR/Disp   05| PD5--DDRD
// DDRC PC1 |A1 LDR                       04| PD4--DDRD
// DDRC PC2 |A2 POT           LEDG/Disp   03| PD3--DDRD
// DDRC PC3 |A3 Select        BOTAO       02| PD2--DDRD
// DDRC PC4 |A4 Disp/ledVM    TX          01| PD1--DDRD
// DDRC PC5 |A5 Disp/ledAM2   RX          00| PD0--DDRD
//          |-------------------------------|
//
#define SetBit(RES, BIT)(RES |= (1 << BIT))   // Por BIT em nível alto
#define ClrBit(RES, BIT)(RES &= ~ (1 << BIT)) // Por BIT em nível baixo
#define TstBit(RES, BIT)(RES &  (1 << BIT))   // testar BIT, retorna 0 ou 1
#define CplBit(RES, BIT)(RES ^= (1 << BIT))   // Inverter estado do BIT

//while (TstBit(PIND, PD2)) {}
//#define SetBit(RES, BIT)(RES |= (1 << BIT))   // Por BIT em nível alto 
//#define ClrBit(RES, BIT)(RES &= ~ (1 << BIT)) // Por BIT em nível baixo
//#define TstBit(RES, BIT)(RES &  (1 << BIT))   // testar BIT, retorna 0 ou 1
//#define CplBit(RES, BIT)(RES ^= (1 << BIT))   // Inverter estado do BIT
//
#define regiA0 DDRC
#define bitiA0 PC0
#define portA0 PORTC
#define regiA1 DDRC
#define bitiA1 PC1
#define portA1 PORTC
#define regiA2 DDRC
#define bitiA2 PC2
#define portA2 PORTC
#define regiA3 DDRC
#define bitiA3 PC3
#define portA3 PORTC
#define regiA4 DDRC
#define bitiA4 PC4
#define portA4 PORTC
#define regiA5 DDRC
#define bitiA5 PC5
#define portA5 PORTC
////////////////////////////////////
#define regiD0 DDRD
#define bitiD0 PD0
#define portD0 PORTD
#define regiD1 DDRD
#define bitiD1 PD1
#define portD1 PORTD
#define regiD2 DDRD
#define bitiD2 PD2
#define portD2 PORTD
#define regiD3 DDRD
#define bitiD3 PD3
#define portD3 PORTD
#define regiD4 DDRD
#define bitiD4 PD4
#define portD4 PORTD
#define regiD5 DDRD
#define bitiD5 PD5
#define portD5 PORTD
#define regiD6 DDRD
#define bitiD6 PD6
#define portD6 PORTD
#define regiD7 DDRD
#define bitiD7 PD7
#define portD7 PORTD
////////////////////////////////////
#define regiD8 DDRB
#define bitiD8 PB0
#define portD8 PORTB
#define regiD9 DDRB
#define bitiD9 PB1
#define portD9 PORTB
#define regiD10 DDRB
#define bitiD10 PB2
#define portD10 PORTB
#define regiD11 DDRB
#define bitiD11 PB3
#define portD11 PORTB
#define regiD12 DDRB
#define bitiD12 PB4
#define portD12 PORTB
#define regiD13 DDRB
#define bitiD13 PB5
#define portD13 PORTB
////////////////////////////////////
