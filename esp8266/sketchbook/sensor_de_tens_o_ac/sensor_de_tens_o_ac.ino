int corrente_inst[300];
int zero = 0;
int diferenca = 0;
int leitura = 0;
int pino_sensor = A0;

float corrente_pico;
float corrente_eficaz;
float tensao_rms;
float tensao_pico;
float frequencia_sinal;

double maior_valor = 0;
double corrente_valor = 0;

unsigned long tempo_zero_inicio;
unsigned long tempo_zero_final;
unsigned long semi_periodo;
unsigned long periodo_completo;

void setup() {
  Serial.begin(9600);
  pinMode(pino_sensor, INPUT);
}

void loop() {
  maior_valor = 0;
  for (int i = 0; i < 300; i++) {
    corrente_inst[i] =  analogRead(pino_sensor);
  }
  for (int i = 0; i < 300; i++) {
    if (maior_valor < corrente_inst[i]) {
      maior_valor = corrente_inst[i];
    }
  }
  //Serial.print("Maior Valor: ");
  //Serial.println(maior_valor);
  delay(1000);

  tensao_pico = map(maior_valor, 500, 661, 0, 313);
  tensao_rms = tensao_pico / 1.77;

  Serial.print("Tensão de Rede Elétrica: ");
  if (tensao_rms < 20)tensao_rms = 0;
  Serial.println  (tensao_rms);
}
