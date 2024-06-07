class Pino {
  private:
    int pino;
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
    unsigned long delayPisca;
    typedef void(funcao)(void);//a função tem que ter um retorno void e não recebe parametros de entrada (void)
    bool btnclicado;
    bool btnliberado;
  public:
    Pino(int pin, int mode) //metodo construtor
    {
      pino = pin;//propriedades do construtor
      if (mode < 1) pinMode(pino, OUTPUT); //propriedades do construtor
      if (mode > 0) pinMode(pino, INPUT); //propriedades do construtor
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
    }//////////////////////////////////////////
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
    }//////////////////////////////////////////
    void Piscar_T(int tmpA, int tmpB) {//metodo piscar controle tempo alto e tempo baixo
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
    void Piscar(long on) { //metodo piscar onda quadrada
      onTime = on;
      unsigned long currentMillis = millis();
      if ((currentMillis - previousMillis >= onTime))
      {
        previousMillis = currentMillis;
        Inverter();
      }
    }//////////////////////////////////////////
    void PulsoA(long on, long off) {//metodo piscar com controle de pulso
      onTime = on;
      offTime = off;
      if ((teste == 0) && (millis() - previousMillis >= onTime)) { //se millis - tempo anterior for > ou = a tempo
        previousMillis = millis();
        Desligar();
        teste = 1;
      }
      if ((teste == 1) && (millis() - previousMillis >= offTime)) {
        previousMillis = millis();
        Ligar();
        teste = 0;
      }
    }//////////////////////////////////////////
    void PulsoB(long off, long on) {//metodo piscar com controle de pulso
      onTime = on;
      offTime = off;
      if ((teste == 0) && (millis() - previousMillis >= offTime)) { //se millis - tempo anterior for > ou = a tempo
        previousMillis = millis();
        Ligar();
        teste = 1;
      }
      if ((teste == 1) && (millis() - previousMillis >= onTime)) {
        previousMillis = millis();
        Desligar();
        teste = 0;
      }
    }//////////////////////////////////////////
    bool Ler_D() {//Lê valor do pino digital
      estado = digitalRead(pino);
      return estado;
    }//////////////////////////////////////////
    int Ler_A() {//Lê valor do pino analogico
      estado_A = analogRead(pino);
      return estado_A;
    }//////////////////////////////////////////
    bool Ler_T(char t) {//Lê valor do pino digital
      estado = touchRead(t);
      return estado;
    }//////////////////////////////////////////
};
//////////////////////////////////////////
Pino botao1(36, 1);
Pino botao2(23, 1);
Pino led1(2, 0); //instanciar obj led1 na classe Pino
//////////////////////////////////////////
void setup() {
  Serial.begin(115200);
}
//////////////////////////////////////////
void loop() {
  Serial.print("    ");
  Serial.print(touchRead(T0));
  Serial.print("    ");
  Serial.print(botao2.Ler_D());
  Serial.print("    ");
  Serial.println(botao1.Ler_A());
  led1.Piscar(100);
}
//////////////////////////////////////////
