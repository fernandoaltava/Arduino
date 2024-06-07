//#include<Arduino.h>

class Pino {
  private:
    int pino;
    bool estado;
    String mode;
    int ultimoEstadoBtn = LOW;
    unsigned long tempoPrimeiroAcionamento = 0;
    unsigned long tempoDebounce = 50;
    unsigned long delayPisca;
    typedef void(funcao)(void);//a função tem que ter um retorno void e não recebe parametros de entrada (void)
    bool btnclicado = false;
    bool btnliberado = false;
  public:
    Pino(int pin, String mode)//metodo construtor
    {
      pino = pin;
      pinMode(pino, mode);
    }

  void Ligar();
    //-------------------------------------------//
    void Desligar();
    //-------------------------------------------//
    void Inverter();
    //-------------------------------------------//
    void Ligar_t(int tmp);
    //-------------------------------------------//
    void Desligar_t(int tmp);
    //-------------------------------------------//
    void Piscar(int tmpA, int tmpB);
    //-------------------------------------------//
    void Clique(funcao *f);
    //-------------------------------------------//
    Ler();
};