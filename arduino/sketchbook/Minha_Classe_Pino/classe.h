class Pino {
  private:
    int pino;
    int repete;
    bool estado;
    bool teste = 0;
    long onTime;
    long offTime;
    int pinoState;
    float estado_A;
    String mode;
    unsigned long previousMillis = 0;
    int ultimoEstadoBtn = LOW;
    unsigned long tempoPrimeiroAcionamento = 0;
    unsigned long tempoDebounce = 50;
    unsigned long delayPisca = 0;
    typedef void(funcao)(void);//a função tem que ter um retorno void e não recebe parametros de entrada (void)
    bool btnclicado;
    bool btnliberado;
  public:
    Pino(int pin, int mode) //metodo construtor
    {
      pino = pin;//propriedades do construtor
      if (mode == 0)pinMode(pino, OUTPUT); //propriedades do construtor
      if (mode == 1)pinMode(pino, INPUT); //propriedades do construtor
    }//os metodos são a ações que podem ser executadas
    //////////////////////////////////////////
    void Ligar() {//metodo ligar
      digitalWrite(pino, HIGH);
      estado = true;
    }//////////////////////////////////////////
    void Desligar() {//metodo desligar
      digitalWrite(pino, LOW);
      estado = false;
    }//////////////////////////////////////////
    void Inverter() {//metodo inverter
      int pinoState = digitalRead(pino);
      digitalWrite(pino, !pinoState);
      estado = !pinoState;
    }//////////////////////////////////////////
    void Piscar(unsigned long on) { //metodo piscar onda quadrada
      onTime = on;
      unsigned long currentMillis = millis();
      if ((currentMillis - previousMillis >= onTime))
      {
        previousMillis = currentMillis;
        Inverter();
      }
    }//////////////////////////////////////////
    void Piscar(unsigned long tmpA, unsigned long tmpB) {//metodo piscar controle tempo alto e tempo baixo
      if ( (millis() - delayPisca) < tmpA ) {
        Ligar();
      }
      if (( (millis() - delayPisca) >= tmpA ) && ((millis() - delayPisca) < (tmpA + tmpB))) {
        Desligar();
      }
      if ((millis() - delayPisca) > (tmpA + tmpB)) {
        delayPisca = millis();
      }
    }//////////////////////////////////////////
    void Clique(funcao *f) {//metodo clique   //rotina Debounce
      int leitura = digitalRead(pino);
      if (leitura != ultimoEstadoBtn) {
        tempoPrimeiroAcionamento = millis();
      }
      if ((millis() - tempoPrimeiroAcionamento) > tempoDebounce) {
        //debounce tratado, comandos que serão executados no acionamento do botão
        if (digitalRead(pino)) {
          btnclicado = true;//true
          btnliberado = false;//false
        } else {
          btnliberado = true;//true
        }
        if ((btnclicado) and (btnliberado)) {
          btnclicado = false;//false
          btnliberado = false;//false
          f();
        }
      }
      ultimoEstadoBtn = leitura;
    }//////////////////////////////////////////
    bool Ler_D() {//Lê valor do pino digital
      estado = digitalRead(pino);
      return estado;
    }//////////////////////////////////////////
    int Ler_A() {//Lê valor do pino analogico
      estado_A = analogRead(pino);
      return estado_A;
    }//////////////////////////////////////////
    void Recebe(bool estate) {//metodo ligar
      digitalWrite(pino, estate);
      estado = estate;
    }//////////////////////////////////////////
    void Repetir(int repete, funcao *f ) {//metodo ligar
//      Serial.println("1"); //IMPRIME O TEXTO NA SERIAL
      for (int x = 0; x <= repete; x++) {
//        Serial.println(x); //IMPRIME O TEXTO NA SERIAL
//        delay(1000);
        f();
      }
    }//////////////////////////////////////////

};
//////////////////FIM DA CLASSE/////////////////////
