#define F_CPU 16000000UL // Cristal de 16MHz
#include <avr/io.h>
#include "util/delay.h"  // Biblioteca para delay
int main(void)
{
  DDRB |= (1 << DDB5); // Configura o PB5 como OUTPUT
  while (1)
  {
    PORTB |= (1 << PORTB5);  // Liga LED
    _delay_ms(500);
    PORTB &= ~(1 << PORTB5); // Desliga LED
    _delay_ms(500);
  }
}
