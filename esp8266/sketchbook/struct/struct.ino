struct Arduino//criação da estrutura de dados
{
  String modelo;//variaveis da estrutura
  int npd;
  int npa;
  float volt;
};
Arduino UNO_R3;//atribuindo UNO_R3 ao nome da estrutura

void setup() {
Serial.begin(115200);
}

void loop() {
UNO_R3.modelo="uno";//atribuindo valores às variaveis da estrutura
UNO_R3.npd=13;
UNO_R3.npa=5;
UNO_R3.volt=5,50;

Serial.println(UNO_R3.modelo);
Serial.println(UNO_R3.npd);
Serial.println(UNO_R3.npa);
Serial.println(UNO_R3.volt);
}
