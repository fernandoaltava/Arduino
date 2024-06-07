#include <Pino.h>
Pino::Pino(int pin){
pino=pin;
pinMode(pino,OUTPUT);
}
   void Pino::ligar() {//metodo ligar
      digitalWrite(pino, HIGH);
    }//////////////////////////////////////////
    void Pino::desligar() {//metodo desligar
      digitalWrite(pino, LOW);
    }//////////////////////////////////////////
    void Pino::inverter() {//metodo inverter
      int pinoState = digitalRead(pino);
      digitalWrite(pino, !pinoState);
    }//////////////////////////////////////////
    void Pino::piscar(long on) { //metodo piscar onda quadrada
      onTime = on;
      unsigned long currentMillis = millis();
      if ((currentMillis - previousMillis >= onTime))
      {
        previousMillis = currentMillis;
        inverter();
      }
    }//////////////////////////////////////////
    void Pino::pulsoA(long on, long off) {//metodo piscar com controle de pulso
      onTime = on;
      offTime = off;
      if ((teste == 0) && (millis() - previousMillis >= onTime)) { //se millis - tempo anterior for > ou = a tempo
        previousMillis = millis();
        desligar();
        teste = 1;
      }
      if ((teste == 1) && (millis() - previousMillis >= offTime)) {
        previousMillis = millis();
        ligar();
        teste = 0;
      }
    }//////////////////////////////////////////
    void Pino::pulsoB(long off, long on) {//metodo piscar com controle de pulso
      onTime = on;
      offTime = off;
      if ((teste == 0) && (millis() - previousMillis >= offTime)) { //se millis - tempo anterior for > ou = a tempo
        previousMillis = millis();
        ligar();
        teste = 1;
      }
      if ((teste == 1) && (millis() - previousMillis >= onTime)) {
        previousMillis = millis();
        desligar();
        teste = 0;
      }
    }//////////////////////////////////////////