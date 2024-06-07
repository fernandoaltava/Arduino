//INFORMAÇÕES//////////////////////////
//Cebolão da Ducato 92°C a 97°C
//Dallas  GPIO 02 pino 04 IN  Bloco
//Dallas  GPIO 15 pino 03 IN  Radiador
//DHT11   GPIO 04 pino 05 IN  Cabine
//Display GPIO 22 pino 14 OUT SCI I2C
//Display GPIO 21 pino 11 OUT SDA I2C
//tecla - GPIO 18 pino 09 IN  pullup
//tecla + GPIO 19 pino 10 IN  pullup
//sirene  GPIO 05 pino 08 OUT
//rele01  GPIO  pino  OUT
//rele02  GPIO  pino  OUT
//BIBLIOTECAS//////////////////////////
//#include <SoftwareSerial.h>
#include <TinyGPS.h>

//SoftwareSerial Serial2(01, 03); // RX, TX
TinyGPS gps1;
#include <TimeLib.h>          // include Arduino time library
#define time_offset   -10800  // define a clock offset of 3600 seconds (1 hour) ==> UTC + 1

#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_PCF8574.h>//amarelo gpio 22 laranja gpio 21
#include <Wire.h>
#include "DHT.h"
//DEFINIÇOES//////////////////////////
#define CHANELL    0          //AUDIO
#define FREQUENCE  6000       //AUDIO
#define RESOLUTION 10         //AUDIO
#define BUZZER_PIN 05         //SIRENE  GPIO 05 pino 08 OUT
#define ONE_WIRE_BLOCO 02     //Dallas  GPIO 02 pino 04 IN  Bloco
#define ONE_WIRE_RADIADOR 15  //Dallas  GPIO 15 pino 03 IN  Radiador
#define DHTPIN 04             //DHT11   GPIO 04 pino 05 IN  Cabine
#define DHTTYPE DHT11         //DHT11  
#define tempoLongo 2000
#define tempoCurto 500

#define RXD2 16
#define TXD2 17

//INSTANCIAS//////////////////////////
OneWire oneWireBloco(ONE_WIRE_BLOCO);
DallasTemperature sensorBloco(&oneWireBloco);
OneWire oneWireRadiador(ONE_WIRE_RADIADOR);
DallasTemperature sensorRadiador(&oneWireRadiador);
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
//VARIAVEIS//////////////////////////
long tempoInicial;
int bloco, umidade, cabineUmidade, valor_Tecla1, valor_Tecla2;
int limiteTemperatura = 80;
float cabineTemperatura, bloco1, agua;
int coluna1 = 0; //Valores para montagem da tela basica
int coluna2 = 5; //Valores para montagem da tela basica
int coluna3 = 8; //Valores para montagem da tela basica
int coluna4 = 12;//Valores para montagem da tela basica
bool ven = 0;
String ven1;
//float tempBloco;
bool piscaTela = 0;
unsigned long tempoAnterior;
int touch = 30;
//PROCEDIMENTOS//////////////////////////
void montaTela();
void valores();
void sensores();
void leTecla();
void pisca();
void autoTeste();
void gpsxx();
//SETUP////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  pinMode(BUZZER_PIN, OUTPUT); //AUDIO//sirene  GPIO 05 pino 08 OUT
  ledcSetup(0, 2000, 10);      //AUDIO//sirene  GPIO 05 pino 08 OUT
  ledcAttachPin(BUZZER_PIN, 0);//AUDIO//sirene  GPIO 05 pino 08 OUT
  int error;
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2 );
  while (!Serial)
    ;
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  if (error == 0) {
    lcd.begin(20, 4); // initializa o lcd
  }//
  lcd.noBlink();
  lcd.noCursor();
  autoTeste();
  dht.begin();
  sensorBloco.begin();
  sensorRadiador.begin();
  montaTela();//monta a tela basica
}//Fim do setup()
//LOOP////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  valor_Tecla1 = touchRead(12); // Touch5 - GPIO12
  valor_Tecla2 = touchRead(27); // Touch7 - GPIO27
  cabineUmidade = dht.readHumidity();
  cabineTemperatura = dht.readTemperature();
  sensorBloco.requestTemperatures(); // Comando para receber a temperatura
  float tempBloco = sensorBloco.getTempCByIndex(0);//dallas
  sensorRadiador.requestTemperatures(); // Comando para receber a temperatura
  float tempRadiador = sensorRadiador.getTempCByIndex(0);//dallas

  Serial.print("Temp Bloco ");// Serial.print("  ");
  Serial.print(tempBloco); Serial.print("  ");
  Serial.print("Temp Radiador ");// Serial.print("  ");
  Serial.print(tempRadiador); Serial.println("  ");
  bloco1 = tempBloco;
  agua = tempRadiador;///////////////////////////////////////////////////
  lcd.setBacklight(1);
  lcd.home();
  sensores();
  gpsxx();
  valores();
  if (bloco1 > limiteTemperatura || agua > limiteTemperatura) {
    pisca();
  } else {
    ledcWriteTone(0, 0);//AUDIO
  }
  ///////////////////////////////////////////////////
  if (valor_Tecla1 <= touch || valor_Tecla2 <= touch) {
    leTecla();
  }//
  ///////////////////////////////////////////////////
}//Fim do loop
//////////////////////////////////////////////////////////////////////////////////////////
void leTecla() {
  lcd.setCursor(coluna4 + 1, 1);
  lcd.blink();
  tempoInicial = millis();
  while ((millis() - tempoInicial < tempoLongo) && valor_Tecla1 <= touch ) {
    if ((millis() - tempoInicial >= tempoLongo) && (valor_Tecla1 <= touch)) {
      limiteTemperatura++;
      sensores();
      valores();
    }
  }
  while ((millis() - tempoInicial < tempoLongo) && valor_Tecla2 <= touch ) {
    if ((millis() - tempoInicial >= tempoLongo) && (valor_Tecla2 <= touch)) {
      limiteTemperatura--;
      sensores();
      valores();
    }
  }
  lcd.noBlink();
}
//////////////////////////////////////////////////////////////////////////////////////////
void pisca() {//pisca a tela como alerta
  if (millis() - tempoAnterior >= 2) {
    tempoAnterior = millis();
    piscaTela = !piscaTela;
    lcd.setBacklight(piscaTela);
    ledcWriteTone(0, 3000);//sirene  GPIO 05 pino 08 OUT
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void valores() {
  lcd.setCursor(coluna2, 1); lcd.print("  ");
  lcd.setCursor(coluna2, 1); lcd.print(bloco1, 0);
  lcd.setCursor(coluna2, 2); lcd.print("  ");
  lcd.setCursor(coluna2, 2); lcd.print(agua, 0);
  lcd.setCursor(coluna2, 3); lcd.print("  ");
  lcd.setCursor(coluna2, 3); lcd.print(cabineTemperatura, 0);
  lcd.setCursor(coluna4, 1); lcd.print("  ");
  lcd.setCursor(coluna4, 1); lcd.print(limiteTemperatura);
  lcd.setCursor(coluna4, 2); lcd.print("  ");
  lcd.setCursor(coluna4, 2); lcd.print(ven1);
  lcd.setCursor(coluna4, 3); lcd.print("  ");
  lcd.setCursor(coluna4, 3); lcd.print(cabineUmidade);
}
//////////////////////////////////////////////////////////////////////////////////////////
void sensores() {
  if (ven == 0)ven1 = "__";
  if (ven == 1)ven1 = "_1";
  if (ven > 1)ven1 = "11";
}
//////////////////////////////////////////////////////////////////////////////////////////
void montaTela() {
  lcd.setCursor(coluna1, 0); lcd.print("Computador de bordo");
  lcd.setCursor(coluna1, 1); lcd.print("Bloc"); lcd.setCursor(coluna3, 1); lcd.print("Lim");
  lcd.setCursor(coluna1, 2); lcd.print("Agua");  lcd.setCursor(coluna3, 2); lcd.print("Ven");
  lcd.setCursor(coluna1, 3); lcd.print("Cabi"); lcd.setCursor(coluna3, 3); lcd.print("Umi");
}
//////////////////////////////////////////////////////////////////////////////////////////
void autoTeste() {
  lcd.clear();
  lcd.setBacklight(1);
  lcd.noBlink();
  lcd.noCursor();
  lcd.home();
  lcd.setCursor(coluna1, 0); lcd.print("12345678901234567890");
  lcd.setCursor(coluna1, 1); lcd.print("12345678901234567890");
  lcd.setCursor(coluna1, 2); lcd.print("12345678901234567890");
  lcd.setCursor(coluna1, 3); lcd.print("12345678901234567890");
  for (int x = 0; x < 8; x++) {
    ledcWriteTone(0, 5000);//sirene  GPIO 05 pino 08 OUT
    delay(100);
    ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
    delay(100);
  }
  for (int x = 0; x < 8; x++) {
    ledcWriteTone(0, 500);//sirene  GPIO 05 pino 08 OUT
    delay(100);
    ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
    delay(100);
  }
  delay(3000);
  lcd.clear();
  lcd.setBacklight(0);
  delay(1000);
  lcd.setBacklight(1);
  ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
  lcd.clear();
  delay(2000);
}
//////////////////////////////////////////////////////////////////////////////////////////
void gpsxx() {
  Serial.println("GPS ");// Serial.print("  ");

  bool recebido = false;
  static unsigned long delayPrint;
  while (Serial2.available()) {
    char cIn = Serial2.read();
    recebido = (gps1.encode(cIn) || recebido);  //Verifica até receber o primeiro sinal dos satelites
  }
  if ( (recebido) && ((millis() - delayPrint) > 1000) ) {  //Mostra apenas após receber o primeiro sinal. Após o primeiro sinal, mostra a cada segundo.
    delayPrint = millis();
    Serial.println("----------------------------------------");
    //Latitude e Longitude
    //long latitude, longitude;
    float latitude, longitude; //As variaveis podem ser float, para não precisar fazer nenhum cálculo
    unsigned long idadeInfo;
    gps1.f_get_position(&latitude, &longitude, &idadeInfo);   //O método f_get_position é mais indicado para retornar as coordenadas em variáveis float, para não precisar fazer nenhum cálculo
    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
      Serial.print("Latitude: ");
      Serial.println(latitude, 6);  //Mostra a latitude com a precisão de 6 dígitos decimais
    }

    if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
      Serial.print("Longitude: ");
      Serial.println(longitude, 6);  //Mostra a longitude com a precisão de 6 dígitos decimais
    }

    if ( (latitude != TinyGPS::GPS_INVALID_F_ANGLE) && (longitude != TinyGPS::GPS_INVALID_F_ANGLE) ) {
      Serial.print("Link para Google Maps:   https://maps.google.com/maps/?&z=10&q=");
      Serial.print(latitude, 6);
      Serial.print(",");
      Serial.println(longitude, 6);
    }

    if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
      Serial.print("Idade da Informacao (ms): ");
      Serial.println(idadeInfo);
    }

    //Dia e Hora
    int ano;
    int hora1;
    byte mes, dia, hora, minuto, segundo, centesimo;
    gps1.crack_datetime(&ano, &mes, &dia, &hora, &minuto, &segundo, &centesimo, &idadeInfo);
    hora = hora - 3;
    if (hora = -3) {
      hora1 = 21;
    }
    else if (hora = -2) {
      hora1 = 22;
    }
    else if (hora = -1) {
      hora1 = 23;
    }
    else {
      hora1 = hora;
    }
    Serial.print("Data (GMT): ");
    Serial.print(dia);
    Serial.print("/");
    Serial.print(mes);
    Serial.print("/");
    Serial.println(ano);

    Serial.print("Horario (GMT): ");
    Serial.print(hora);
    Serial.print(":");
    Serial.print(minuto);
    Serial.print(":");
    Serial.print(segundo);
    Serial.print(":");
    Serial.println(centesimo);

    //altitude
    float altitudeGPS;
    altitudeGPS = gps1.f_altitude();

    if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 1000000)) {
      Serial.print("Altitude (cm): ");
      Serial.println(altitudeGPS);
    }

    //velocidade
    float velocidade;
    //velocidade = gps1.speed();        //nós
    velocidade = gps1.f_speed_kmph();   //km/h
    //velocidade = gps1.f_speed_mph();  //milha/h
    //velocidade = gps1.f_speed_mps();  //milha/segundo

    Serial.print("Velocidade (km/h): ");
    Serial.println(velocidade, 2);  //Conversão de Nós para Km/h

    //sentito (em centesima de graus)
    unsigned long sentido;
    sentido = gps1.course();

    Serial.print("Sentido (grau): ");
    Serial.println(float(sentido) / 100, 2);

    //satelites e precisão
    unsigned short satelites;
    unsigned long precisao;
    satelites = gps1.satellites();
    precisao =  gps1.hdop();

    if (satelites != TinyGPS::GPS_INVALID_SATELLITES) {
      Serial.print("Satelites: ");
      Serial.println(satelites);
    }

    if (precisao != TinyGPS::GPS_INVALID_HDOP) {
      Serial.print("Precisao (centesimos de segundo): ");
      Serial.println(precisao);
    }

    //float distancia_entre;
    //distancia_entre = gps1.distance_between(lat1, long1, lat2, long2);
    //float sentido_para;
    //sentido_para = gps1.course_to(lat1, long1, lat2, long2);
  }
}




















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
