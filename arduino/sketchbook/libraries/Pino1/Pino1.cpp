#include <Pino1.h>
Pino1::Pino1(int pin){
pino=pin;
pinMode(pino,OUTPUT);
}
   void Pino1::ligar() {//metodo ligar
      digitalWrite(pino, HIGH);
    }//////////////////////////////////////////
    void Pino1::desligar() {//metodo desligar
      digitalWrite(pino, LOW);
    }//////////////////////////////////////////
    void Pino1::inverter() {//metodo inverter
      int pinoState = digitalRead(pino);
      digitalWrite(pino, !pinoState);
    }//////////////////////////////////////////
    void Pino1::piscar(long on) { //metodo piscar onda quadrada
      onTime = on;
      unsigned long currentMillis = millis();
      if ((currentMillis - previousMillis >= onTime))
      {
        previousMillis = currentMillis;
        inverter();
      }
    }//////////////////////////////////////////
    void Pino1::pulsoA(long on, long off) {//metodo piscar com controle de pulso
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
    void Pino1::pulsoB(long off, long on) {//metodo piscar com controle de pulso
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

uint8_t Pino1::attach(int pin, int min, int max)
{
  if(this->servoIndex < MAX_SERVOS ) {
    pinMode( pin, OUTPUT) ;                                   // set servo pin to output
    servos[this->servoIndex].Pin.nbr = pin;
    // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128
    this->min  = (MIN_PULSE_WIDTH - min)/4; //resolution of min/max is 4 us
    this->max  = (MAX_PULSE_WIDTH - max)/4;
    // initialize the timer if it has not already been initialized
    timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
    if(isTimerActive(timer) == false)
      initISR(timer);
    servos[this->servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
  }
  return this->servoIndex ;
}