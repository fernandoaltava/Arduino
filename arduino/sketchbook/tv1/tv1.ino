#include <OneWire.h> //INCLUSÃO DE BIBLIOTECA
#include <DallasTemperature.h> //INCLUSÃO DE BIBLIOTECA

#define DS18B20 6 //DEFINE O PINO DIGITAL UTILIZADO PELO SENSOR

OneWire ourWire(DS18B20); //CONFIGURA UMA INSTÂNCIA ONEWIRE PARA SE COMUNICAR COM O SENSOR
DallasTemperature sensors(&ourWire); //BIBLIOTECA DallasTemperature UTILIZA A OneWire


#include <TVout.h>
#include <fontALL.h>
TVout tv;

void setup() {
  Serial.begin(9600);
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A3, INPUT);
  pinMode(A2, INPUT);
  // put your setup code here, to run once:
  tv.begin(_NTSC, 680, 320);
  //tv.begin(_PAL);
  //tv.begin(_NTSC,680,360);
  sensors.begin(); //INICIA O SENSOR
}

void loop() {

  sensors.requestTemperatures();//SOLICITA QUE A FUNÇÃO INFORME A TEMPERATURA DO SENSOR
  //int x=sensors.getTempCByIndex(0);
  Serial.print("Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(sensors.getTempCByIndex(0)); //IMPRIME NA SERIAL O VALOR DE TEMPERATURA MEDIDO
  Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL
  

  int a = map(analogRead(A5), 0, 1023, 0, 130); //remapeia a5 para valor entre 0 e 80
  int b = map(analogRead(A4), 0, 1023, 0, 80); //remapeia a5 para valor entre 0 e 80
  int c = map(analogRead(A3), 0, 1023, 0, 60); //remapeia a5 para valor entre 0 e 80
  int d = map(analogRead(A2), 0, 1023, 0, 100); //remapeia a5 para valor entre 0 e 80
  int coluna = 2;
  int linha = 18; //maximo 18
  tv.draw_rect(coluna + 107, linha, 25, 57, 0, 0); //apaga todos os valores



  //tv.fill(1);
  //  tv.draw_rect(0, 0, 167, 63, 1, 1);
  //  tv.draw_line(20, 50, 20, 10, 1);
  //  tv.draw_row(15, 10, 20, 1);
  //  tv.draw_column(30, 0, 20, 1);
  tv.select_font(font8x8ext);
  tv.draw_circle(coluna + 138, linha, 1, 1);
  tv.print(coluna, linha, "Temp. Motor");
  tv.print(coluna + 108, linha, a );
  tv.print(coluna + 141, linha, "C");

  /*  tv.print(coluna, linha+10, "Combustivel");
    tv.print(coluna+108, linha+10, b);
    tv.print(coluna+141, linha+10, "L");

    tv.draw_circle(coluna+138, linha+29, 1, 1);
    tv.print(coluna, linha+28, "Temp. Cabine");
    tv.print(coluna+108, linha+28, c);
    tv.print(coluna+141, linha+28, "C");

    tv.print(coluna, linha+38, "Humidade");
    tv.print(coluna+108, linha+38, d);
    tv.print(coluna+141, linha+38, "%");
    tv.select_font(font4x6);
    tv.print(2, 2, "Fernando Altava de lima");

  */
  delay(100);
  // tv.fill(0);

}
