unsigned long int tempoAnterior1 = 0;
byte led1 = 13;
boolean estado1 = LOW;

unsigned long int tempoAnterior2 = 0;
byte led2 = 12;
boolean estado2 = LOW;

void thread1(int tempo);
void thread2(int tempo);

void setup() {
  Serial.begin(9600);
  pinMode(led1, estado1);
  pinMode(led2, estado2);
}

void loop() {

  thread1(1000);
  thread2(300);

//    if (millis() - tempoAnterior1 >= tempo) {//se millis - tempo anterior for > ou = a tempo
//    tempoAnterior1 = millis();
//    estado1 = !estado1;
//    digitalWrite(led1, estado1);
//  }

}

void thread1(int tempo) {
  if (millis() - tempoAnterior1 >= tempo) {//se millis - tempo anterior for > ou = a tempo
    tempoAnterior1 = millis();
    estado1 = !estado1;
    digitalWrite(led1, estado1);
  }
}

void thread2(int tempo) {
  if (millis() - tempoAnterior2 >= tempo) {
    tempoAnterior2 = millis();
    estado2 = !estado2;
    digitalWrite(led2, estado2);
  }
}
//.h prototipo das classes, metodos
//.cpp logica
//keywords 
//pbjetos são instancias das classes
