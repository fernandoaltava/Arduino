#include<Arduino.h>

class Pino {
public:
    Pino(int pin);
    int pino;
    bool estado;
    bool teste = 0;
    long onTime;
    long offTime;
    long on;
    long off;
    int pinoState;
    unsigned long previousMillis = 0;
    void ligar();
    void desligar();
    void inverter();
    void piscar(long on);
    void pulsoA(long on, long off);
    void pulsoB(long off, long on);
};
