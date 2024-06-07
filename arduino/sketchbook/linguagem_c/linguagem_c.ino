// --- Interrupção ---
ISR(TIMER0_OVF_vect)
{
  static int baset1 = 0,           //variável local estática para base de tempo 1
             baset2 = 0;           //variável local estática para base de tempo 2

  TCNT0 = 0x06;                    //reinicializa Timer0

  //TEMPO de 1ms
  baset1 ++;                       //incrementa baset1 em 1 a cada ms
  baset2 ++;                       //incrementa baset2 em 1 a cada ms

  if (baset1 == 1000)
  {
    //TEMPO de 1000ms
    baset1 = 0;                    //reinicia baset1
    PORTB ^= (1 << PORTB5);        //inverte o estado de digital 13 (PB5)

  } //end if

  if (baset2 == 741)
  {
    //TEMPO de 741ms
    baset2 = 0;
    //um segundo evento que será controlado a cada 741ms

  } //end if

} //end ISR


// =========================================================
// --- Função Principal ---
int main()
{

  DDRB  |=  (1 << PORTB5);         //configura digital 13 (PB5) como saída
  PORTB &= ~(1 << PORTB5);         //inicializa digital 13 (PB5) em LOW

  cli();                           //desliga interrupções
  TCNT0  = 0x06;                   //inicia Timer0 para contar até 250
  TCCR0B = 0x03;                   //prescaler 1:64
  TIMSK0 = 0x01;                   //habilita interrupção do Timer0
  sei();                           //liga interrupções

  //BASE DE TEMPO PRINCIPAL = 62.5E-9 x 64 x 250 = 1ms

  while (1);                       //apenas aguarda interrupções

  return 0;                        //retorna 0 (precisa retornar algo, pois a função main é do tipo int)

} //end main


/* ============================================================================

                                       _
                                      / \
                                     |oo >
                                     _\=/_
                    ___         #   /  _  \   #
                   /<> \         \\//|/.\|\\//
                 _|_____|_        \/  \_/  \/
                | | === | |          |\ /|
                |_|  0  |_|          \_ _/
                 ||  0  ||           | | |
                 ||__*__||           | | |
                |* \___/ *|          []|[]
                /=\ /=\ /=\          | | |
  ________________[_]_[_]_[_]_________/_]_[_\_______________________________


  ============================================================================ */
/* --- Final do Programa --- */
