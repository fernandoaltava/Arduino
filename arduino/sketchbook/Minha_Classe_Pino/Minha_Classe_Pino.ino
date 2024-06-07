#include "classe.h"
//typedef void(funcao1)(void);
#include "MillisTimer.h"
// Cria um timer.
MillisTimer timer1 = MillisTimer();
/////////////////////////////////////
Pino lm35(A0, 1); //instanciar obj na classe Pino
Pino botao(2, 1); //instanciar obj na classe Pino
Pino ldr(A1, 1); //instanciar obj na classe Pino
Pino pot(A2, 1); //instanciar obj na classe Pino
Pino seletor(A3, 0); //instanciar obj na classe Pino
Pino ledg(8, 0); //instanciar obj na classe Pino
Pino ledy1(7, 0); //instanciar obj na classe Pino
Pino ledy2(A5, 0); //instanciar obj na classe Pino
Pino ledr(A4, 0); //instanciar obj na classe Pino
Pino led13(13, 0); //instanciar obj na classe Pino
Pino red(5, 0); //instanciar obj na classe Pino
Pino green(3, 0); //instanciar obj na classe Pino
Pino blue(6, 0); //instanciar obj na classe Pino
/////////////////////////////////////
void teste1(int xx) {
  switch (xx) {
    case 1:
      red.Piscar(100);
      break;
    case 2:
      green.Piscar(100);
      break;
    case 3:
      blue.Piscar(100);
      break;
      default:
      red.Inverter();
      green.Inverter();
      blue.Inverter();
      break;
      
  }
}
void teste() {
  green.Inverter();
}
//void Repetir(int repete, funcao1 *f );
void piscaLedr();
void piscaLedg();
void piscaLedy1();
void piscaLedy2();
/////////////////////////////////////
void setup() {
  Serial.begin(115200);
  timer1.setInterval(100);//
  timer1.expiredHandler(teste1);//
  timer1.setRepeats(50);//Repetição
  timer1.start();//Inicio
}//Fim do setup
/////////////////////////////////////
void loop() {
  seletor.Ligar();
  /*  if (pot.Ler_A() < ldr.Ler_A()) {
      seletor.Ligar();
      if (pot.Ler_A() <= 40) {
        blue.Piscar(ldr.Ler_A());
        red.Desligar();
        green.Desligar();
      }
      if (pot.Ler_A() <= 80 && pot.Ler_A() > 40) {
        red.Piscar(ldr.Ler_A());
        blue.Desligar();
        green.Desligar();
      }
      if (pot.Ler_A() <= 120 && pot.Ler_A() > 80) {
        green.Piscar(ldr.Ler_A());
        blue.Desligar();
        red.Desligar();
      }
    }//Fim do if*/
  if (pot.Ler_A() > 200) {
    //timer1.setInterval(100);//
    //timer1.expiredHandler(teste);//
    timer1.setRepeats(100);//Repetição
    timer1.start();//Inicio    //      seletor.Desligar();
    Serial.println(">200"); //IMPRIME O TEXTO NA SERIAL
    //timer1.run();//

  }
  ledg.Piscar(100, 400);
  ledy1.Piscar(200, 300);
  ledy2.Piscar(300, 200);
  ledr.Piscar(400, 100);
  //green.Repetir(5, teste);
  //delay(100000);
  if (botao.Ler_D()) {
    Serial
    .print("LDR=");
    Serial.print(ldr.Ler_A());
    Serial.print(" POT=");
    Serial.print(pot.Ler_A());
    float temperatura = (lm35.Ler_A() * 0.0048828125 * 100); //VARIÁVEL RECEBE A TEMPERATURA MEDIDA
    Serial.print(" Temperatura="); //IMPRIME O TEXTO NA SERIAL
    Serial.print(temperatura); //IMPRIME NA SERIAL A TEMPERATURA MEDIDA
    Serial.println("°C"); //IMPRIME O TEXTO NA SERIAL
    timer1.run();//
  }
  timer1.run();//
  //timer1.run();//
  if (!timer1.isRunning())
  {
    teste1(3);
    Serial.println(Constant("Timer finished!"));
    //for (;;);//Instrução para travar a execução
  }
}//Fim do loop
/////////////////////////////////////
