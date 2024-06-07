const int pinoSensor = A2;// Declara pinoSensor como pino A2
float tensaoEntrada = 0.0;// Inicia os valores de tensaoEntrada em 0
float tensaoMedida = 0.0;// Inicia os valores de tensaoMedida em 0
float valorR1 =  330000.0;// Define valorR1 como 30k Ohms
float valorR2 = 1000000.0;// Define valorR2 como 7,5k Ohms
float vref = 16;// Define vref como 5V
int leituraSensor = 0;// Inicia a leituraSensor em 0
void setup() {
  pinMode(pinoSensor, INPUT);// Define o pinoSensor como entrada de sinal
  Serial.begin(9600);
}

void loop() {
  leituraSensor = analogRead(pinoSensor);// Chama de leituraSensor o valor analógico
  // Realiza os cálculos de conversão para valores vistos no artigo
  tensaoEntrada = (leituraSensor * vref) / 1023.0;
  tensaoMedida = tensaoEntrada / (valorR2 / (valorR1 + valorR2));
  // Imprime os valores no monitor serial para possíveis verificações
  Serial.print("Tensão DC medida: ");
  Serial.print(tensaoMedida);
  Serial.println("V");
  delay(500);
}
