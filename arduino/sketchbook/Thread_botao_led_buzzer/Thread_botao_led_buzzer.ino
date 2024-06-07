unsigned long int tempo_atual = 0;
unsigned long ultimo_tempo = 0;

void setup() {

  pinMode(10, INPUT);//botao
  pinMode(2, OUTPUT);//led
  pinMode(3, OUTPUT);//led
  pinMode(6, OUTPUT);//buzzer
}

void loop() {

  bool pino = digitalRead(10);
  tempo_atual = millis();

  if (pino == 0)//se botao solto
  {
    digitalWrite(2, LOW);//apaga led
    digitalWrite(3, LOW);//apaga led
    digitalWrite(6, LOW);//desliga buzzer
    ultimo_tempo = tempo_atual;
  }

  if ((pino == 1) && (tempo_atual - ultimo_tempo >= 3000))//se botao pressionado e 3 segundos se passou
  {
    digitalWrite(2, HIGH);//liga led
    digitalWrite(3, HIGH);//liga led
    digitalWrite(6, HIGH);//liga buzzer
    ultimo_tempo = tempo_atual;
  }
}
