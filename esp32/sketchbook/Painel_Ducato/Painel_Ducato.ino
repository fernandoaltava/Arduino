//Cebolão da Ducato 92°C a 97°C
//sirene GPIO 15 pino 3
//DHT11  GPIO 04 pino 5
//Dallas GPIO 16 pino 8
//valor_tecla1 tecla + = touchRead(12); // Touch5 - GPIO12
//valor_tecla2 tecla - = touchRead(14); // Touch6 - GPIO14

#include <SPI.h>
#define CHANELL    0
#define FREQUENCE  6000
#define RESOLUTION 10
#define BUZZER_PIN GPIO_NUM_15//SIRENE
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 16
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#include <LiquidCrystal_PCF8574.h>//amarelo gpio 22 laranja gpio 21
#include <Wire.h>
#include "DHT.h"
#define DHTPIN 4//gpio 04
#define DHTTYPE DHT11
#define tempoLongo 2000
#define tempoCurto 500
long tempoInicial;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
int bloco, umidade, cabineu, valor_tecla1, valor_tecla2;
int limite = 80;
float cabinet, bloco1, agua;
int coluna1 = 0;
int coluna2 = 5;
int coluna3 = 8;
int coluna4 = 12;
bool ven = 0;
String ven1;
float tempC;
bool xx = 0;
unsigned long tempoAnterior;
int touch = 30;
void tela();
void valores();
void sensores();
void tecla();
void pisca();

//////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  int error;
  Serial.begin(115200);
  while (!Serial)
    ;
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();

  if (error == 0) {
    lcd.begin(20, 4); // initialize the lcd
  }//Fim do if

  lcd.noBlink();
  lcd.noCursor();
  dht.begin();
  sensors.begin();
  pinMode(BUZZER_PIN, OUTPUT);
  ledcSetup(0, 2000, 10);
  ledcAttachPin(BUZZER_PIN, 0);
  tela();
}//Fim do setup()
//////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  valor_tecla1 = touchRead(12); // Touch5 - GPIO12
  valor_tecla2 = touchRead(27); // Touch7 - GPIO27
  cabineu = dht.readHumidity();
  cabinet = dht.readTemperature();
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempC = sensors.getTempCByIndex(0);//dallas
  Serial.print(tempC); Serial.print("  ");
  Serial.print(valor_tecla1); Serial.print("  ");
  Serial.println(valor_tecla2);
  bloco1 = tempC;
  agua = bloco1;///////////////////////////////////////////////////
  lcd.setBacklight(1);
  lcd.home();
  //lcd.scrollDisplayRight();
  //tela();
  sensores();
  valores();
  if (bloco1 > limite) {
    pisca();
  } else {
    ledcWriteTone(0, 0);
  }
  ///////////////////////////////////////////////////
  if (valor_tecla1 <= touch || valor_tecla2 <= touch) {
    tecla();
  }//Fim do if
  ///////////////////////////////////////////////////
}//Fim do loop
//////////////////////////////////////////////////////////////////////////////////////////
void tecla() {
  lcd.setCursor(coluna4+1, 1);
  lcd.blink();
  tempoInicial = millis();
  while ((millis() - tempoInicial < tempoLongo) && valor_tecla1 <= touch ) {
    if ((millis() - tempoInicial >= tempoLongo) && (valor_tecla1 <= touch)) {
      limite++;
      //    tela();
      sensores();
      valores();
    }
  }
  while ((millis() - tempoInicial < tempoLongo) && valor_tecla2 <= touch ) {
    if ((millis() - tempoInicial >= tempoLongo) && (valor_tecla2 <= touch)) {
      limite--;
      //    tela();
      sensores();
      valores();
    }
  }

  lcd.noBlink();

  /*
    if (valor_tecla1 <= 30) {
      limite++;
      //    tela();
      sensores();
      valores();
    }
    if (valor_tecla2 <= 30) {
      limite--;
      //    tela();
      sensores();
      valores();
    }
  */


}
//////////////////////////////////////////////////////////////////////////////////////////
void pisca() {//pisca a tela como alerta
  if (millis() - tempoAnterior >= 2) {
    tempoAnterior = millis();
    xx = !xx;
    lcd.setBacklight(xx);
    ledcWriteTone(0, 3000);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void valores() {
  lcd.setCursor(coluna2, 1); lcd.print("  ");
  lcd.setCursor(coluna2, 1); lcd.print(bloco1, 0);
  lcd.setCursor(coluna2, 2); lcd.print("  ");
  lcd.setCursor(coluna2, 2); lcd.print(agua, 0);
  lcd.setCursor(coluna2, 3); lcd.print("  ");
  lcd.setCursor(coluna2, 3); lcd.print(cabinet, 0);
  lcd.setCursor(coluna4, 1); lcd.print("  ");
  lcd.setCursor(coluna4, 1); lcd.print(limite);
  lcd.setCursor(coluna4, 2); lcd.print("  ");
  lcd.setCursor(coluna4, 2); lcd.print(ven1);
  lcd.setCursor(coluna4, 3); lcd.print("  ");
  lcd.setCursor(coluna4, 3); lcd.print(cabineu);
}
//////////////////////////////////////////////////////////////////////////////////////////
void sensores() {
  if (ven == 0)ven1 = "__";
  if (ven == 1)ven1 = "_1";
  if (ven > 1)ven1 = "11";

}
//////////////////////////////////////////////////////////////////////////////////////////
void tela() {
  lcd.setCursor(coluna1, 0); lcd.print("Computador de bordo");
  lcd.setCursor(coluna1, 1); lcd.print("Bloc"); lcd.setCursor(coluna3, 1); lcd.print("Lim");
  lcd.setCursor(coluna1, 2); lcd.print("Agua");  lcd.setCursor(coluna3, 2); lcd.print("Ven");
  lcd.setCursor(coluna1, 3); lcd.print("Cabi"); lcd.setCursor(coluna3, 3); lcd.print("Umi");
}
//////////////////////////////////////////////////////////////////////////////////////////
/*
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Hello LCD");
    lcd.cursor();
    lcd.blink();
    lcd.noBlink();
    lcd.noCursor();
    lcd.noDisplay();
    lcd.setCursor(0, 0);
    lcd.scrollDisplayLeft();
    lcd.scrollDisplayRight();
*/
