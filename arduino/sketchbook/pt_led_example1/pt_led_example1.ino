 /* Exemplo de código para demonstrar o uso de protothreads
  * Ele alterna um LED usando dois protothreads independentes. 
  * Um pt alterna todos 1000ms, o outro a cada 900ms. 
  * O resultado é um padrão intermitente.*/
#include <pt.h>   // 
#define LEDPIN 13  // LEDPIN é uma constante 
static struct pt pt1, pt2; // cada protothread precisa de um destes
void setup() {
  pinMode(LEDPIN, OUTPUT); // LED init
  PT_INIT(&pt1);  // initialise the two
  PT_INIT(&pt2);  // protothread variables
}
void toggleLED() {
  boolean ledstate = digitalRead(LEDPIN); // get LED state
  ledstate ^= 1;   // altera o estado de ledstate usando xor
  digitalWrite(LEDPIN, ledstate); // escreva ledstate em ledpin
}
/* Esta função alterna o LED após 'intervalo' ms passado */
static int protothread1(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) { // nunca pare
    /* cada vez que a função é chamada de segundo booleano
     * argumento "millis () - timestamp> intervalo" é reavaliado
     * e se for falso, a função sai depois disso. */
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis(); // take a new timestamp
    toggleLED();
  }
  PT_END(pt);
}
/* exatamente o mesmo que a função protothread1 */
static int protothread2(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) {
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis();
    toggleLED();
  }
  PT_END(pt);
}
void loop() {
  protothread1(&pt1, 900); // agendar os dois protothreads
  protothread2(&pt2, 1000); // chamando-os infinitamente
}
