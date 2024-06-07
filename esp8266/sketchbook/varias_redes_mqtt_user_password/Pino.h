/* -----------Metodos da classe Pino-------------------
   Ligar()
   Desligar()
   Inverter()
   Ligar_T(int tmp)
   Desligar_T(int tmp)
   Piscar(int tmpA, int tmpB)
   Clique(funcao)
   Ler()
   Ler_A()
   Pino *pino1(13, OUTPUT);//mode 0 OUTPUT o * indica ponteiro//instancia objeto
   Pino pino2(12, OUTPUT);//instancia objeto
   Pino pino3(2, INPUT_PULLUP);//instancia objeto
   pino1->Inverter();// -> faz o apontamento pois pino1 é um ponteiro
   pino2.Inverter();//pino 2 não precisa de -> pois não é um ponteiro
*/
//--------------Inicio da Classe Pino--------------------//
class Pino {
  public:
    int pino;
    bool estado;
    int estado_A;
    String mode;
    //    long timeHigh,timeLow,atraso,mref,ajuste,resto;
    int ultimoEstadoBtn = LOW;
    unsigned long tempoPrimeiroAcionamento = 0;
    unsigned long tempoDebounce = 50;
    unsigned long delayPisca;
    //typedef void(funcao)();//a função tem que ter um retorno void e não recebe parametros de entrada (void)
    typedef void(funcao)(void);//a função tem que ter um retorno void e não recebe parametros de entrada (void)
    //typedef retorno (nome_função)(parâmetros de entrada);
    //-------------------------------------------//
    bool btnclicado;
    bool btnliberado;
    //-------------------------------------------//
    Pino(int pin, int mode)//metodo construtor
    {
      btnclicado = false;
      btnliberado = false;
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
    void Ligar_T(int tmp) {//metodo acender_t
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
    void Desligar_T(int tmp) {//metodo apagar_t
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
    }
    //-------------------------------------------//
//    Ler() {
//      estado = digitalRead(pino);
//      return estado;
//    }
    //-------------------------------------------//
//    Ler_A() {
//      estado_A = analogRead(pino);
//      return estado_A;
//    }
    //-------------------------------------------//

};
//--------------Fim da Classe Pino-----------------------//
int time(long timeHigh, long timeLow, long atraso, long mref = 0) {//
  long ajuste = mref % (timeHigh + timeLow);
  long resto  = (millis() + timeHigh + timeLow - ajuste - atraso) % (timeHigh + timeLow);
  return (resto < timeHigh ? HIGH : LOW);
}

boolean time1(unsigned long * mref, unsigned long t) {
  if (millis() > t && millis() - *mref > t) {
    *mref = millis();
    return true;
  }
  return false;
}
