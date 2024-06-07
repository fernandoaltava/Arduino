#include "EmonLib.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

EnergyMonitor SCT01301;
EnergyMonitor SCT01302;
EnergyMonitor SCT01303;

String estado;
int coluna = 0;
int pinSCT01 = A0;   //Pino analógico conectado ao SCT-013
int pinSCT02 = A1;   //Pino analógico conectado ao SCT-013
int pinSCT03 = A2;   //Pino analógico conectado ao SCT-013

int tensao = 127;
int tensao2 = 220;

int potencia01;
int potencia02;
int potencia03;
bool x = 0;

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4); // 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void conta_tempo(void(*p)(), String descricao) {
  long m1, m2;
  m1 = millis();
  (*p)();//executa a função
  m2 = millis();
  Serial.print(descricao + ": m1= ");
  Serial.print(m1);
  Serial.print(" - m2 = ");
  Serial.print(m2);
  Serial.print(" - dif = ");
  Serial.print(m2 - m1);
  Serial.println(" milisegundos");
}

void mascara();
void tela(int linha,  int potencia, String estado);
void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd
  //lcd.init();
  lcd.backlight();
  SCT01301.current(pinSCT01, 60.607);
  SCT01302.current(pinSCT02, 60.607);
  SCT01303.current(pinSCT03, 60.607);
  lcd.begin(4, 20);
  lcd.clear();
  //mascara();
  conta_tempo(mascara, "mascara");
}

void loop()
{
  potencia01 = (SCT01301.calcIrms(1480)) * tensao;          // Calcula o valor da Potencia Instantanea
  potencia02 = (SCT01302.calcIrms(1480)) * tensao;          // Calcula o valor da Potencia Instantanea
  potencia03 = (SCT01303.calcIrms(1480)) * tensao;          // Calcula o valor da Potencia Instantanea
  if (x == 0)estado = "GASTANDO";
  else estado = "ECONOMIA";
  tela(1,  potencia01, estado);
  tela(2,  potencia02, estado);
  tela(3,  potencia03, estado);
delay(500);
  x = !x;
}
void tela(int linha,  int potencia, String estado) {
  lcd.setCursor(3, linha);
  lcd.print("      ");
  lcd.setCursor(3, linha);
  lcd.print(potencia);
  lcd.setCursor(11, linha);
  lcd.print("         ");
  lcd.setCursor(11, linha);
  lcd.print(estado);
}
void mascara() {
  lcd.setCursor(3, 0);
  lcd.print("Wattimetro FAL");
  lcd.setCursor(0, 1);
  lcd.print("P1 ");
  lcd.setCursor(0, 2);
  lcd.print("P2 ");
  lcd.setCursor(0, 3);
  lcd.print("P3 ");
  lcd.setCursor(9, 1);
  lcd.print("W");
  lcd.setCursor(9, 2);
  lcd.print("W");
  lcd.setCursor(9, 3);
  lcd.print("W");

}
