//Programa: Digispark ATtiny85 com display OLED I2C
//Autor: Arduino e Cia

#include <DigisparkOLED.h>
#include <Wire.h>

void setup()
{
  //Inicializa o display
  oled.begin();
}

void loop()
{
  //Preenche o display
  oled.fill(0xFF);
  delay(3000);
  
  //Limpa o display
  oled.clear();
  delay(1000);
  
  //Posiciona o cursor
  //oled.setCursor(X em pixels, Y em linhas de 8 pixels comecando com 0);
  oled.setCursor(10, 0);
  //Seleciona fonte 8x16
  oled.setFont(FONT8X16);
  oled.print(F("Arduino e Cia"));
  //Seleciona fonte 6x8
  oled.setFont(FONT6X8);
  oled.setCursor(8, 3);
  oled.print(F("Digispark ATtiny85"));
  oled.setCursor(25, 6);
  oled.print(F("Display OLED"));
  
  //Aguarda 10 segundos e reinicia o processo
  delay(10000);
}
