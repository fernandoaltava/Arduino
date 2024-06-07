extern volatile unsigned long timer0_millis;//variavel para reset do millis

unsigned long tempoAgora = 0;
unsigned long tempoLeitura1 = 0;
unsigned long tempoLeitura2 = 0;

void setup() {

  Serial.begin(9600);
  tempoLeitura1 = millis();
  tempoLeitura2 = millis();

}

void loop() {
  if (millis() > 4000000000) {//se millis esta no limite de 50 dias 4.320.000.000 ms
    noInterrupts();//desabilita interrupções
    timer0_millis = 0;//zera o millis
    interrupts();//habilita interrupções
    tempoLeitura1 = millis();
    tempoLeitura2 = millis();
  }

  float leitura1 = 0;
  float leitura2 = 0;

  tempoAgora = millis();
  if ((tempoAgora - tempoLeitura1) >= 500) {//1° thread
    for (int i = 0; i < 10; i++) {    //faz 10 amostragens
      leitura1 += analogRead(1);
    }
    leitura1 = leitura1 / 10;         //tira a  média
    leitura1 = (leitura1 * 5) / 1023; //transforma em volts
    Serial.print("S1:  ");
    Serial.println(leitura1);
    tempoLeitura1 = millis();
  }
  tempoAgora = millis();
  if ((tempoAgora - tempoLeitura2) >= 1000) {//2° thread
    for (int i = 0; i < 10; i++) {    //faz 10 amostragens
      leitura2 += analogRead(2);
    }
    leitura2 = leitura2 / 10;        //tira a  média
    leitura2 = (leitura2 * 5) / 1023;//transforma em volts
    Serial.print("S2:  ");
    Serial.println(leitura2);
    tempoLeitura2 = millis();
  }
}
