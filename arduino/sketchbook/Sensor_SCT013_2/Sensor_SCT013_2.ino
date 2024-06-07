#include "EmonLib.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

EnergyMonitor SCT01301;
EnergyMonitor SCT01302;
EnergyMonitor SCT01303;

int pinSCT01 = A1;   //Pino analógico conectado ao SCT-013
int pinSCT02 = A2;   //Pino analógico conectado ao SCT-013
int pinSCT03 = A3;   //Pino analógico conectado ao SCT-013

int tensao = 127;
int tensao2 = 220;

int potencia01;
int potencia02;
int potencia03;

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4); // 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void mascara();
void tela(int linha, double corrente, int potencia);
void setup()
{
  lcd.init();                      // initialize the lcd
  //lcd.init();
  lcd.backlight();
  SCT01301.current(pinSCT01, 60.607);
  SCT01302.current(pinSCT02, 60.607);
  SCT01303.current(pinSCT03, 60.607);
  lcd.begin(4, 20);
  lcd.clear();
  mascara();


}

void loop()
{
  double Irms01 = SCT01301.calcIrms(1480);   // Calcula o valor da Corrente
  potencia01 = Irms01 * tensao;          // Calcula o valor da Potencia Instantanea
  double Irms02 = SCT01302.calcIrms(1480);   // Calcula o valor da Corrente
  potencia02 = Irms02 * tensao;          // Calcula o valor da Potencia Instantanea
  double Irms03 = SCT01303.calcIrms(1480);   // Calcula o valor da Corrente
  potencia03 = Irms03 * tensao2;          // Calcula o valor da Potencia Instantanea

  tela(1, Irms01, potencia01);
  tela(2, Irms02, potencia02);
  tela(3, Irms03, potencia03);


  //delay(1);
}
void tela(int linha, double corrente, int potencia) {
  lcd.setCursor(3, linha);
  lcd.print("      ");
  lcd.setCursor(3, linha);
  lcd.print(corrente);
  lcd.setCursor(14, linha);
  lcd.print("     ");
  lcd.setCursor(14, linha);
  lcd.print(potencia);

}
void mascara() {
  lcd.setCursor(3, 0);
  lcd.print("Wattimetro FAL");
  lcd.setCursor(0, 1);
  lcd.print("C1 ");
  lcd.setCursor(0, 2);
  lcd.print("C2 ");
  lcd.setCursor(0, 3);
  lcd.print("C3 ");
  lcd.setCursor(9, 1);
  lcd.print("A");
  lcd.setCursor(11, 1);
  lcd.print("P1 ");
  lcd.setCursor(9, 2);
  lcd.print("A");
  lcd.setCursor(11, 2);
  lcd.print("P2 ");
  lcd.setCursor(9, 3);
  lcd.print("A");
  lcd.setCursor(11, 3);
  lcd.print("P3 ");
  lcd.setCursor(19, 1);
  lcd.print("W");
  lcd.setCursor(19, 2);
  lcd.print("W");
  lcd.setCursor(19, 3);
  lcd.print("W");
}
