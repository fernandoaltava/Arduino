//--------------Inicio da Classe Pino--------------------//
class Pino {
  //  public:
  private:
    int pino;
    bool estado;
    //String mode;
    int mode;
    int ultimoEstadoBtn = LOW;
    unsigned long tempoPrimeiroAcionamento = 0;
    unsigned long tempoDebounce = 50;
    unsigned long delayPisca;
    //typedef void(funcao)();//a função tem que ter um retorno void e não recebe parametros de entrada (void)
    typedef void(funcao)(void);//a função tem que ter um retorno void e não recebe parametros de entrada (void)
    //typedef retorno (nome_função)(parâmetros de entrada);
    //-------------------------------------------//
    bool btnclicado = false;
    bool btnliberado = false;
  public:
    Pino(int pin, int mode)//metodo construtor
    {
      pino = pin;
      pinMode(pino, mode);
    }
    //-------------------------------------------//
    void Ligar() {//metodo acender
      digitalWrite(pino, HIGH);
      estado = true;
    }
    //-------------------------------------------//
    void Desligar() {//metodo apagar
      digitalWrite(pino, LOW);
      estado = false;
    }
    //-------------------------------------------//
    void Inverter() {//metodo inverter
      int estadoLed = digitalRead(pino);
      digitalWrite(pino, !estadoLed);
      estado = !estadoLed;
    }
    //-------------------------------------------//
    void Ligar_t(int tmp) {//metodo acender_t
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
    void Desligar_t(int tmp) {//metodo apagar_t
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
    void Piscar(int tmpA, int tmpB) {//metodo piscar
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
    void Clique(funcao *f) {//metodo clique
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
  int Ler() {
      estado = digitalRead(pino);
      return estado;
    }
    //-------------------------------------------//
};
//--------------Fim da Classe Pino-----------------------//
