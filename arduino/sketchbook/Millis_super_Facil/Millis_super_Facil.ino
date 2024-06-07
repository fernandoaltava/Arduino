unsigned long int tempo_atual = 0;
unsigned long ultimo_tempo = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(10, INPUT);
}

void loop() {
  bool pino = digitalRead(10);
  tempo_atual = millis();

  if (pino == 0) {//se botao esta solto ultimo_tempo = tempo_atual e pino 2 0
    digitalWrite(2, LOW);
    ultimo_tempo = tempo_atual;
  }
  if ((pino == 1) && (tempo_atual - ultimo_tempo >= 3000)) {//enquanto botao apertado ultimo_tempo para de ser atualizado
    digitalWrite(2, HIGH);
    ultimo_tempo = tempo_atual;
  }
}
