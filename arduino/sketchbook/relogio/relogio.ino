//Programa : Relogio com modulo RTC DS1307
//Autor : FILIPEFLOP
#include <Wire.h> 
//Carrega a biblioteca do RTC DS1307
#include <DS1307.h>
 
//Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
DS1307 rtc(4, 5);
 
void setup()
{
  //Aciona o relogio
  rtc.halt(false);
  rtc.begin();
   
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  rtc.setDOW(WEDNESDAY);      //Define o dia da semana
  rtc.setTime(18, 06, 0);     //Define o horario
  rtc.setDate(17, 6, 2020);   //Define o dia, mes e ano
   
  //Definicoes do pino SQW/Out
  //rtc.setSQWRate(SQW_RATE_1);
  //rtc.enableSQW(true);
   
  Serial.begin(57600);
}
 
void loop()
{
  //Mostra as informações no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
   
  //Aguarda 1 segundo e repete o processo
  delay (1000);
}
