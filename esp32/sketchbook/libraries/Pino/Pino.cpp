#include <Pino.h>
Pino::Pino(int pin){
pino=pin;
pinMode(pino,mode);
}
    //-------------------------------------------//
    void Pino::Ligar() {//metodo acender
      digitalWrite(pino, HIGH);
      estado = true;
    }
    //-------------------------------------------//
    void Pino::Desligar() {//metodo apagar
      digitalWrite(pino, LOW);
      estado = false;
    }
    //-------------------------------------------//
    void Pino::Inverter() {//metodo inverter
      int estadoLed = digitalRead(pino);
      digitalWrite(pino, !estadoLed);
      estado = !estadoLed;
    }
    //-------------------------------------------//
    void Pino::Ligar_t(int tmp) {//metodo acender_t
      if ( (millis() - delayPisca) < tmp ) {
        Ligar();
      } else {
        Desligar();
      }
      if ( (millis() - delayPisca) >= tmp * 2 ) {
        delayPisca = millis();
      }
      estado = true;
    }
    //-------------------------------------------//
    void Pino::Desligar_t(int tmp) {//metodo apagar_t
      if ( (millis() - delayPisca) < tmp ) {
        Desligar();
      } else {
        Ligar();
      }
      if ( (millis() - delayPisca) >= tmp * 2 ) {
        delayPisca = millis();
      }
      estado = false;
    }
    //-------------------------------------------//
    void Pino::Piscar(int tmpA, int tmpB) {//metodo piscar
      if ( (millis() - delayPisca) < tmpA ) {
        Ligar();
      }
      if (( (millis() - delayPisca) >= tmpA ) && ((millis() - delayPisca) < (tmpA + tmpB))) {
        Desligar();
      }
      if ((millis() - delayPisca) > (tmpA + tmpB)) {
        delayPisca = millis();
      }
    }
    //-------------------------------------------//
    void Pino::Clique(funcao *f) {//metodo clique
      //rotina Debounce
      int leitura = digitalRead(pino);
      if (leitura != ultimoEstadoBtn) {
        tempoPrimeiroAcionamento = millis();
      }
      if ((millis() - tempoPrimeiroAcionamento) > tempoDebounce) {
        //debounce tratado, comandos que serão executados no acionamento do botão
        if (digitalRead(pino)) {
          btnclicado = true;
          btnliberado = false;
        } else {
          btnliberado = true;
        }
        if ((btnclicado) and (btnliberado)) {
          btnclicado = false;
          btnliberado = false;
          f();
        }
      }
      ultimoEstadoBtn = leitura;
    }
    //-------------------------------------------//
    Pino::Ler() {
      estado = digitalRead(pino);
      return estado;
    }
    //-------------------------------------------//