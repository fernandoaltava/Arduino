// --- Interrupção ---
ISR(TIMER0_OVF_vect)
{ //50ms, 70ms, 130ms, 264ms, 741ms
  static int thr1 = 0,           //variável local estática para base de tempo 1
             thr2 = 0,           //variável local estática para base de tempo 2
             thr3 = 0,
             thr4 = 0,
             thr5 = 0;
  //base de tempo de 1ms
  thr1++;
  thr2++;
  thr3++;
  thr4++;
  thr5++;

  TCNT0 = 0x06;                    //reinicializa Timer0

  if (thr1 == 50)
  {
    //TEMPO de 50ms
    thr1 = 0;                    //reinicia baset1
    PORTD ^= (1 << PORTD3);        //inverte o estado de digital 13 (PB5)
  } //end if

  if (thr2 == 70)
  {
    //TEMPO de 50ms
    thr2 = 0;                    //reinicia baset1
    PORTD ^= (1 << PORTD4);        //inverte o estado de digital 13 (PB5)
  } //end if

  if (thr3 == 130)
  {
    //TEMPO de 50ms
    thr3 = 0;                    //reinicia baset1
    PORTD ^= (1 << PORTD5);        //inverte o estado de digital 13 (PB5)
  } //end if

  if (thr4 == 264)
  {
    //TEMPO de 50ms
    thr4 = 0;                    //reinicia baset1
    PORTD ^= (1 << PORTD6);        //inverte o estado de digital 13 (PB5)
  } //end if

  if (thr5 == 741)
  {
    //TEMPO de 50ms
    thr5 = 0;                    //reinicia baset1
    PORTD ^= (1 << PORTD7);        //inverte o estado de digital 13 (PB5)
  } //end if





} //end ISR


// =========================================================
// --- Função Principal ---
int main()
{

  DDRD  |=  (1 << PORTD7) | //configura digital 7 (PD7) como saída
            (1 << PORTD6) | //configura digital 6 (PD6) como saída
            (1 << PORTD5) | //configura digital 5 (PD5) como saída
            (1 << PORTD4) | //configura digital 4 (PD4) como saída
            (1 << PORTD3);  //configura digital 3 (PD3) como saída


  PORTD &= ~(1 << PORTD7) | //inicializa digital 7 (PD7) em LOW//HIGH
           ~(1 << PORTD6) | //inicializa digital 6 (PD6) em LOW//HIGH
           ~(1 << PORTD5) | //inicializa digital 5 (PD5) em LOW//HIGH
           ~(1 << PORTD4) | //inicializa digital 4 (PD4) em LOW//HIGH
           ~(1 << PORTD3);  //inicializa digital 3 (PD3) em LOW//HIGH

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
