//INFORMAÇÕES//////////////////////////
//Cebolão da Ducato 92°C a 97°C
//Marcador de combustivel cheio 32 Ohms, médio 150 Ohms e vazio 300 Ohms
//
//Dallas  GPIO 02 pino 04 IN  Bloco
//Dallas  GPIO 15 pino 03 IN  Radiador
//Display GPIO 22 pino 14 OUT SCI I2C
//Display GPIO 21 pino 11 OUT SDA I2C
//sirene  GPIO 05 pino 08 OUT
//BIBLIOTECAS//////////////////////////
#include <TinyGPS.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_PCF8574.h>//amarelo gpio 22 laranja gpio 21
#include <Wire.h>

#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

//#include "DHT.h"
//DEFINIÇOES//////////////////////////
#define CHANELL    0          //AUDIO
#define FREQUENCE  6000       //AUDIO
#define RESOLUTION 10         //AUDIO
#define BUZZER_PIN 05         //SIRENE  GPIO 05 pino 08 OUT
#define ONE_WIRE_BLOCO 02     //Dallas  GPIO 02 pino 04 IN  Bloco
#define ONE_WIRE_RADIADOR 15  //Dallas  GPIO 15 pino 03 IN  Radiador
//#define DHTPIN 04             //DHT11   GPIO 04 pino 05 IN  Cabine
//#define DHTTYPE DHT11         //DHT11
#define tempoLongo 2000
#define tempoCurto 500
#define RXD2 16
#define TXD2 17
//#define time_offset   -10800  // define a clock offset of 3600 seconds (1 hour) ==> UTC + 1
//INSTANCIAS//////////////////////////
TinyGPS gps1;
OneWire oneWireBloco(ONE_WIRE_BLOCO);
DallasTemperature sensorBloco(&oneWireBloco);
OneWire oneWireRadiador(ONE_WIRE_RADIADOR);
DallasTemperature sensorRadiador(&oneWireRadiador);
//DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
//VARIAVEIS//////////////////////////
long tempoInicial;
int bloco;
int limiteTemperatura = 90;//92°C até 97°C
float bloco1, agua;
//int limiteVelocidade = 50;
//int diesel = 80;
//bool ven = 0;
//String ven1;
//float tempBloco;
bool piscaTela = 0;
unsigned long tempoAnterior;
//int touch = 30;
int hora1;
int colunaBloco, colunaAgua, colunaVelocidade = 10;
int velocidade;
////////////////////////////////////
bool recebido = false;
static unsigned long delayPrint;
float latitude, longitude; //As variaveis podem ser float, para não precisar fazer nenhum cálculo
unsigned long idadeInfo;
int ano;
byte mes, dia, hora, minuto, segundo, centesimo;
float altitudeGPS;
float velocidade1;
unsigned long sentido;
unsigned short satelites;
unsigned long precisao;
/////////////////////////////////////
hw_timer_t *timer = NULL; //faz o controle do temporizador (interrupção por tempo)
//PROCEDIMENTOS//////////////////////////
void montaTela();
void valores();
void pisca();
void autoTeste();
void gpsxx();
void converteHora();
//SETUP////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  SerialBT.begin("ESP32test"); //Bluetooth device name
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
  //  dht.begin();
  sensorBloco.begin();
  sensorRadiador.begin();
  montaTela();//monta a tela basica
  valores();
}//Fim do setup()

//LOOP////////////////////////////////////////////////////////////////////////////////////////
void loop() {
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
  gpsxx();
  //  velocidade = (velocidade1, 0);
  valores();
  if (bloco1 > limiteTemperatura || agua > limiteTemperatura) {
    pisca();
  } else {
    ledcWriteTone(0, 0);//AUDIO
  }
  ///////////////////////////////////////////////////
  Serial.print(hora1);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.println(segundo);
  SerialBT.print(hora1);
  SerialBT.print(":");
  SerialBT.print(minuto);
  SerialBT.print(":");
  SerialBT.println(segundo);
}//Fim do loop
////////////////////////////////////////////
void montaTela() {//coluna,linha
  lcd.setCursor(15, 0); lcd.print("  :  ");//hora
  lcd.setCursor( 0, 1); lcd.print("Bloco ");
  lcd.setCursor( 10, 1); lcd.print("----------");
  ////////////
  lcd.setCursor( 0, 2); lcd.print("Agua  ");
  lcd.setCursor( 10, 2); lcd.print("----------");
  ////////////
  lcd.setCursor( 0, 3); lcd.print("Veloc ");
  lcd.setCursor( 10, 3); lcd.print("----------");
  //timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
}//fim do montatela
//////////////////////////////////////////////////////////////////////////////////////////
void valores() {
  lcd.setCursor(0, 0); lcd.print("  ");
  if (satelites < 10) {
    lcd.setCursor(1, 0); lcd.print(satelites);
  } else {
    lcd.setCursor(0, 0); lcd.print(satelites);
  }////fim do satelites
  /////////////
  ////inicio precisao
  lcd.setCursor(3, 0); lcd.print("   ");
  if (precisao < 10) {
    lcd.setCursor(5, 0); lcd.print(precisao);
  } else if (precisao < 100) {
    lcd.setCursor(4, 0); lcd.print(precisao);
  } else {
    lcd.setCursor(3, 0); lcd.print(precisao);
  }
}////fim do precisao
/////////////
/////inicio Horario
lcd.setCursor(15, 0); lcd.print("  ");
if (hora1 < 10) {
  lcd.setCursor(16, 0); lcd.print(hora1);
} else {
  lcd.setCursor(15, 0); lcd.print(hora1);
}
lcd.setCursor(18, 0); lcd.print("  ");
if (minuto < 10) {
  lcd.setCursor(18, 0); lcd.print("0");
  lcd.setCursor(19, 0); lcd.print(minuto);
} else {
  lcd.setCursor(18, 0); lcd.print(minuto);
}/////fim Horario
/////////////
/////inicio temperatura do bloco digital
lcd.setCursor(6, 1); lcd.print("   ");
if (bloco1 < 100) {
  lcd.setCursor(7, 1); lcd.print(bloco1, 0);
} else {
  lcd.setCursor(6, 1); lcd.print(bloco1, 0);
}/////fim temperatura do bloco digital
/////////////
/////inicio temperatura da agua digital
lcd.setCursor(6, 2); lcd.print("   ");
if (agua < 100) {
  lcd.setCursor(7, 2); lcd.print(agua, 0);
} else {
  lcd.setCursor(6, 2); lcd.print(agua, 0);
}/////fim temperatura da agua digital
/////////////
//////inicio velocidade digital
lcd.setCursor(6, 3); lcd.print("   ");
if (velocidade < 10) {
  lcd.setCursor(8, 3); lcd.print(velocidade);
} else if (velocidade < 100) {
  lcd.setCursor(7, 3); lcd.print(velocidade);
} else {
  lcd.setCursor(6, 3); lcd.print(velocidade);
}
//////fim velocidade digital
/////////////
/////inicio temperatura do bloco analogica
lcd.setCursor( 10, 1); lcd.print("----------");
if (bloco1 >= 55 && bloco1 < 60)colunaBloco = 10;
if (bloco1 >= 60 && bloco1 < 65)colunaBloco = 11;
if (bloco1 >= 65 && bloco1 < 70)colunaBloco = 12;
if (bloco1 >= 70 && bloco1 < 75)colunaBloco = 13;
if (bloco1 >= 75 && bloco1 < 80)colunaBloco = 14;
if (bloco1 >= 80 && bloco1 < 85)colunaBloco = 15;
if (bloco1 >= 85 && bloco1 < 90)colunaBloco = 16;
if (bloco1 >= 90 && bloco1 < 95)colunaBloco = 17;
if (bloco1 >= 95 && bloco1 < 100)colunaBloco = 18;
if (bloco1 >= 100)colunaBloco = 19;
if (bloco1 > 55) {
  lcd.setCursor( colunaBloco, 1); lcd.print("#");
}
}/////fim temperatura do bloc analogica
/////////////
/////inicio temperatura da agua analogica
lcd.setCursor( 10, 2); lcd.print("----------");
if (agua >= 55 && agua < 60)colunaAgua = 10;
if (agua >= 60 && agua < 65)colunaAgua = 11;
if (agua >= 65 && agua < 70)colunaAgua = 12;
if (agua >= 70 && agua < 75)colunaAgua = 13;
if (agua >= 75 && agua < 80)colunaAgua = 14;
if (agua >= 80 && agua < 85)colunaAgua = 15;
if (agua >= 85 && agua < 90)colunaAgua = 16;
if (agua >= 90 && agua < 95)colunaAgua = 17;
if (agua >= 95 && agua < 100)colunaAgua = 18;
if (agua >= 100)colunaAgua = 19;
if (agua > 55) {
  lcd.setCursor( colunaAgua, 2); lcd.print("#");
}
}/////fim temperatura da agua analogica
/////////////
//////inicio velocidade analogica
lcd.setCursor( 10, 3); lcd.print("----------");
if (velocidade >= 20 && velocidade < 30)colunaVelocidade = 10;
if (velocidade >= 30 && velocidade < 40)colunaVelocidade = 11;
if (velocidade >= 40 && velocidade < 50)colunaVelocidade = 12;
if (velocidade >= 50 && velocidade < 60)colunaVelocidade = 13;
if (velocidade >= 60 && velocidade < 70)colunaVelocidade = 14;
if (velocidade >= 70 && velocidade < 80)colunaVelocidade = 15;
if (velocidade >= 80 && velocidade < 90)colunaVelocidade = 16;
if (velocidade >= 90 && velocidade < 100)colunaVelocidade = 17;
if (velocidade >= 100 && velocidade < 110)colunaVelocidade = 18;
if (velocidade >= 110)colunaVelocidade = 19;
if (velocidade > 20) {
  lcd.setCursor( colunaVelocidade, 3); lcd.print("#");
}/////fim velocidade analogica
}//fim do valores
//////////////////////////////////////////////////////////////////////////////////////////
void gpsxx() {
  SerialBT.println("                 GPS1");
  while (Serial2.available()) {
    char cIn = Serial2.read();
    recebido = (gps1.encode(cIn) || recebido);  //Verifica até receber o primeiro sinal dos satelites
  }//fim do while (Serial2.available())
  SerialBT.println("                 GPS2");
  if ( (recebido) && ((millis() - delayPrint) > 1000) ) {  //Mostra apenas após receber o primeiro sinal. Após o primeiro sinal, mostra a cada segundo.
    delayPrint = millis();
    SerialBT.println("                 GPS3");
    Serial.println("----------------------------------------");
    //Latitude e Longitude
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
    SerialBT.print("Latitude  ");
    SerialBT.println(latitude, 6);
    SerialBT.print("Longitude  ");
    SerialBT.println(longitude, 6);
    if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
      Serial.print("Idade da Informacao (ms): ");
      Serial.println(idadeInfo);
    }
    SerialBT.print("Idade da informação  ");
    SerialBT.println(idadeInfo);
    //Dia e Hora
    gps1.crack_datetime(&ano, &mes, &dia, &hora, &minuto, &segundo, &centesimo, &idadeInfo);
    converteHora();
    Serial.print("Data (GMT): ");
    Serial.print(dia);
    Serial.print("/");
    Serial.print(mes);
    Serial.print("/");
    Serial.println(ano);
    ////////////////////////////
    Serial.print("Horario (GMT): ");
    Serial.print(hora1);
    Serial.print(":");
    Serial.print(minuto);
    Serial.print(":");
    Serial.print(segundo);
    Serial.print(":");
    Serial.println(centesimo);
    SerialBT.print(hora1);
    SerialBT.print(":");
    SerialBT.print(minuto);
    SerialBT.print(":");
    SerialBT.println(segundo);
    //altitude
    altitudeGPS = gps1.f_altitude();
    if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 1000000)) {
      Serial.print("Altitude (cm): ");
      Serial.println(altitudeGPS);
    }
    SerialBT.print("Altitude  ");
    SerialBT.println(altitudeGPS);
    //velocidade
    velocidade1 = gps1.f_speed_kmph();   //km/h
    int velocidade = (velocidade1, 0);
    Serial.print("Velocidade (km/h): ");
    Serial.println(velocidade1, 2);  //Conversão de Nós para Km/h
    SerialBT.print("VelocidadeGPS  ");
    SerialBT.println(velocidade1, 0);
    SerialBT.print("VelocidadeINT  ");
    SerialBT.println(velocidade, 0);
    //sentido (em centesima de graus)
    sentido = gps1.course();
    Serial.print("Sentido (grau): ");
    Serial.println(float(sentido) / 100, 2);
    SerialBT.print("Sentido  ");
    SerialBT.println(float(sentido) / 100, 2);
    //satelites e precisão
    satelites = gps1.satellites();
    precisao =  gps1.hdop();
    if (satelites != TinyGPS::GPS_INVALID_SATELLITES) {
      Serial.print("Satelites: ");
      Serial.println(satelites);
    }//fim do if (satelites != TinyGPS::GPS_INVALID_SATELLITES)
    if (precisao != TinyGPS::GPS_INVALID_HDOP) {
      Serial.print("Precisao (centesimos de segundo): ");
      Serial.println(precisao);
    }//fim do if (precisao != TinyGPS::GPS_INVALID_HDOP)
    SerialBT.print("Satelites  ");
    SerialBT.println(satelites);
    SerialBT.print("Precisão  ");
    SerialBT.println(precisao);
    //float distancia_entre;
    //distancia_entre = gps1.distance_between(lat1, long1, lat2, long2);
    //float sentido_para;
    //sentido_para = gps1.course_to(lat1, long1, lat2, long2);
  }//fim do if ( (recebido) && ((millis() - delayPrint) > 1000) )
}//fim do gpsxx
//////////////////////////////////////////////////////////////////////////////////////////
void pisca() {//pisca a tela como alerta
  if (millis() - tempoAnterior >= 2) {
    tempoAnterior = millis();
    piscaTela = !piscaTela;
    lcd.setBacklight(piscaTela);
    ledcWriteTone(0, 3000);//sirene  GPIO 05 pino 08 OUT
  }
}//fim do pisca
//////////////////////////////////////////////////////////////////////////////////////////
void autoTeste() {
  lcd.clear();
  lcd.setBacklight(1);
  lcd.noBlink();
  lcd.noCursor();
  lcd.home();
  agua = 0;
  bloco1 = 0;
  velocidade = 0;
  montaTela();
  delay(2000);
  for (int a = 0; a < 101; a++) {
    valores();
    bloco1++;
    agua++;
    velocidade++;
    delay(1);
  }
  for (int a = 100; a > 0; a--) {
    valores();
    bloco1--;
    agua--;
    velocidade--;
    delay(1);
  }
  agua, bloco1, velocidade = 0;

  for (int x = 0; x < 8; x++) {
    ledcWriteTone(0, 5000);//sirene  GPIO 05 pino 08 OUT
    delay(100);
    ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
    delay(100);
  }
  for (int x = 0; x < 8; x++) {
    ledcWriteTone(0, 1000);//sirene  GPIO 05 pino 08 OUT
    delay(100);
    ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
    delay(100);
  }
  delay(100);
  lcd.clear();
  lcd.setBacklight(0);
  delay(1000);
  lcd.setBacklight(1);
  ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
  lcd.clear();
  delay(200);
  montaTela();
}//fim do autoteste
//////////////////////////////////////////////////////////////////////////////////////////
void converteHora() {
  switch (hora) {
    case 0:
      hora1 = 21; break;
    case 1:
      hora1 = 22; break;
    case 2:
      hora1 = 23; break;
    case 3:
      hora1 = 0; break;
    case 4:
      hora1 = 1; break;
    case 5:
      hora1 = 2; break;
    case 6:
      hora1 = 3; break;
    case 7:
      hora1 = 4; break;
    case 8:
      hora1 = 5; break;
    case 9:
      hora1 = 6; break;
    case 10:
      hora1 = 7; break;
    case 11:
      hora1 = 8; break;
    case 12:
      hora1 = 9; break;
    case 13:
      hora1 = 10; break;
    case 14:
      hora1 = 11; break;
    case 15:
      hora1 = 12; break;
    case 16:
      hora1 = 13; break;
    case 17:
      hora1 = 14; break;
    case 18:
      hora1 = 15; break;
    case 19:
      hora1 = 16; break;
    case 20:
      hora1 = 17; break;
    case 21:
      hora1 = 18; break;
    case 22:
      hora1 = 19; break;
    case 23:
      hora1 = 20; break;
    default:

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
