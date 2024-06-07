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
#include <TinyGPS.h>
#include <TimeLib.h>          // include Arduino time library
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
#define time_offset   -10800  // define a clock offset of 3600 seconds (1 hour) ==> UTC + 1
//INSTANCIAS//////////////////////////
TinyGPS gps1;
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
int limiteVelocidade = 50;
int diesel = 80;
bool ven = 0;
String ven1;
//float tempBloco;
bool piscaTela = 0;
unsigned long tempoAnterior;
int touch = 30;
int ano;
int hora1;
byte mes, dia, hora, minuto, segundo, centesimo;
float velocidade;
hw_timer_t *timer = NULL; //faz o controle do temporizador (interrupção por tempo)
//PROCEDIMENTOS//////////////////////////
void IRAM_ATTR resetModule();
void montaTela();
void valores();
void sensores();
void leTecla();
void pisca();
void autoTeste();
void gpsxx();


/////OTA////////////////////////////////////
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <Update.h>
const char* ssid = "Luana2";
const char* password = "40224022";
IPAddress local_ip(192, 168, 1, 83);
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);
const uint32_t PORTA = 80; //A porta que será utilizada (padrão 80)
//Algumas informações que podem ser interessantes
const uint32_t chipID = (uint32_t)(ESP.getEfuseMac() >> 32); //um ID exclusivo do Chip...
const String CHIP_ID = "<p> Chip ID: " + String(chipID) + "</p>"; // montado para ser usado no HTML
const String VERSION = "<p> Versão: 3.0 </p>"; //Exemplo de um controle de versão
//Informações interessantes agrupadas
const String INFOS = VERSION + CHIP_ID;
//Sinalizador de autorização do OTA
boolean OTA_AUTORIZADO = false;
//inicia o servidor na porta selecionada
//aqui testamos na porta 3000, ao invés da 80 padrão
WebServer server(PORTA);
//Páginas HTML utilizadas no procedimento OTA
String verifica = "<!DOCTYPE html><html><head><title>ESP32 webOTA</title><meta charset='UTF-8'></head><body><h1>ESP32 webOTA</h1><h2>Digite a chave de verificação.<p>Clique em ok para continuar. . .</p></h2>" + INFOS + "<form method='POST' action='/avalia 'enctype='multipart/form-data'> <p><label>Autorização: </label><input type='text' name='autorizacao'></p><input type='submit' value='Ok'></form></body></html>";
String serverIndex = "<!DOCTYPE html><html><head><title>ESP32 webOTA</title><meta charset='UTF-8'></head><body><h1>ESP32 webOTA</h1><h2>Selecione o arquivo para a atualização e clique em atualizar.</h2>" + INFOS + "<form method='POST' action='/update' enctype='multipart/form-data'><p><input type='file' name='update'></p><p><input type='submit' value='Atualizar'></p></form></body></html>";
String Resultado_Ok = "<!DOCTYPE html><html><head><title>ESP32 webOTA</title><meta charset='UTF-8'></head><body><h1>ESP32 webOTA</h1><h2>Atualização bem sucedida!</h2>" + INFOS + "</body></html>";
String Resultado_Falha = "<!DOCTYPE html><html><head><title>ESP32 webOTA</title><meta charset='UTF-8'></head><body><h1>ESP32 webOTA</h1><h2>Falha durante a atualização. A versão anterior será recarregado.</h2>" + INFOS + "</body></html>";
/////OTA////////////////////////////////////
//Setup
void setup(void)
{
/////OTA////////////////////////////////////
  Serial.begin(115200); //Serial para debug
  WiFi.mode(WIFI_AP_STA); //Comfigura o ESP32 como ponto de acesso e estação
  WiFi.begin(ssid, password);// inicia a conexão com o WiFi
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (WiFi.status() == WL_CONNECTED) //aguarda a conexão
  {
    server.on("/", HTTP_GET, []() //atende uma solicitação para a raiz
    {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", verifica);
    });
    server.on("/avalia", HTTP_POST, [] ()
    {
      Serial.println("Em server.on /avalia: args= " + String(server.arg("autorizacao"))); //somente para debug
      if (server.arg("autorizacao") != "123456") // confere se o dado de autorização atende a avaliação
      {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", Resultado_Falha);
      }
      else
      {
        OTA_AUTORIZADO = true;
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", serverIndex);
      }
    });
    server.on("/serverIndex", HTTP_GET, []()
    {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", serverIndex);
    });
    server.on("/update", HTTP_POST, []()
    {
      if (OTA_AUTORIZADO == false)
      {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", Resultado_Falha);
        return;
      }
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", (Update.hasError()) ? Resultado_Falha : Resultado_Ok);
      delay(1000);
      ESP.restart();
    }, []()
    {
      HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START)
      {
        Serial.setDebugOutput(true);
        Serial.printf("Atualizando: %s\n", upload.filename.c_str());
        if (!Update.begin())
        {
          Update.printError(Serial);
        }
      }
      else if (upload.status == UPLOAD_FILE_WRITE)
      {
        if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
        {
          Update.printError(Serial);
        }
      }
      else if (upload.status == UPLOAD_FILE_END)
      {
        if (Update.end(true))
        {
          Serial.printf("Atualização bem sucedida! %u\nReiniciando...\n", upload.totalSize);
        }
        else
        {
          Update.printError(Serial);
        }
        Serial.setDebugOutput(false);
      }
      else
      {
        Serial.printf("Atualização falhou inesperadamente! (possivelmente a conexão foi perdida.): status=%d\n", upload.status);
      }
    });
    server.begin(); //inicia o servidor
    Serial.println(INFOS); //envia as informações armazenadas em INFOS, para debug
    Serial.print("Servidor em: ");
    Serial.println( WiFi.localIP().toString() + ":" + PORTA);
  }
  else
  {
    Serial.println("Falha ao conectar ao WiFi.");
  }
/////OTA////////////////////////////////////
  pinMode(BUZZER_PIN, OUTPUT); //AUDIO//sirene  GPIO 05 pino 08 OUT
  ledcSetup(0, 2000, 10);      //AUDIO//sirene  GPIO 05 pino 08 OUT
  ledcAttachPin(BUZZER_PIN, 0);//AUDIO//sirene  GPIO 05 pino 08 OUT
  int error;
  //Serial.begin(115200);
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
  timer = timerBegin(0, 80, true); //timerID 0, div 80mhz
  //timerAttachInterrupt(timer, &resetModule, true);
  //timerAlarmWrite(timer, 12000000, true);//tempo de estouro = 9 segundos
  //timerAlarmEnable(timer); //habilita a interrupção

}
///////////////////////////////////////
void loop(void)
{
/////OTA////////////////////////////////////
  server.handleClient();
  delay(1);//somente um instante
/////OTA////////////////////////////////////
  valor_Tecla1 = touchRead(12); // Touch5 - GPIO12
  valor_Tecla2 = touchRead(27); // Touch7 - GPIO27
  cabineUmidade = dht.readHumidity();
  cabineTemperatura = dht.readTemperature();
  sensorBloco.requestTemperatures(); // Comando para receber a temperatura
  float tempBloco = sensorBloco.getTempCByIndex(0);//dallas
  sensorRadiador.requestTemperatures(); // Comando para receber a temperatura
  float tempRadiador = sensorRadiador.getTempCByIndex(0);//dallas

  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  //  Serial.print("Temp Bloco ");// Serial.print("  ");
  //  Serial.print(tempBloco); Serial.print("  ");
  //  Serial.print("Temp Radiador ");// Serial.print("  ");
  //  Serial.print(tempRadiador); Serial.println("  ");
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
  //  Serial.print(hora1);
  //  Serial.print(":");
  //  Serial.print(minuto);
  //  Serial.print(":");
  //  Serial.print(segundo);

}

////////////////////////////////////////////
void IRAM_ATTR resetModule() {
  esp_restart(); //reinicia o chip
}
//////////////////////////////////////////////////////////////////////////////////////////
void leTecla() {
}
//////////////////////////////////////////////////////////////////////////////////////////
void pisca() {//pisca a tela como alerta
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  if (millis() - tempoAnterior >= 2) {
    tempoAnterior = millis();
    piscaTela = !piscaTela;
    lcd.setBacklight(piscaTela);
    ledcWriteTone(0, 3000);//sirene  GPIO 05 pino 08 OUT
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void sensores() {
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  if (ven == 0)ven1 = "__";
  if (ven == 1)ven1 = "_1";
  if (ven > 1)ven1 = "11";
}
//////////////////////////////////////////////////////////////////////////////////////////
void autoTeste() {
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  lcd.clear();
  lcd.setBacklight(1);
  lcd.noBlink();
  lcd.noCursor();
  lcd.home();
  lcd.setCursor(0, 0); lcd.print("11111111111111111111");
  lcd.setCursor(0, 1); lcd.print("12345678901234567890");
  lcd.setCursor(0, 2); lcd.print("12345678901234567890");
  lcd.setCursor(0, 3); lcd.print("12345678901234567890");
  for (int x = 0; x < 8; x++) {
    ledcWriteTone(0, 5000);//sirene  GPIO 05 pino 08 OUT
    delay(100);
    ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
    delay(100);
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  }
  for (int x = 0; x < 8; x++) {
    ledcWriteTone(0, 500);//sirene  GPIO 05 pino 08 OUT
    delay(100);
    ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
    delay(100);
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  }
  delay(100);
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  lcd.clear();
  lcd.setBacklight(0);
  delay(1000);
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  lcd.setBacklight(1);
  ledcWriteTone(0, 0);//sirene  GPIO 05 pino 08 OUT
  lcd.clear();
  delay(200);
}
//////////////////////////////////////////////////////////////////////////////////////////
void gpsxx() {
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  bool recebido = false;
  static unsigned long delayPrint;
  while (Serial2.available()) {
    char cIn = Serial2.read();
    recebido = (gps1.encode(cIn) || recebido);  //Verifica até receber o primeiro sinal dos satelites
  }
  if ( (recebido) && ((millis() - delayPrint) > 1000) ) {  //Mostra apenas após receber o primeiro sinal. Após o primeiro sinal, mostra a cada segundo.
    delayPrint = millis();
    float latitude, longitude; //As variaveis podem ser float, para não precisar fazer nenhum cálculo
    unsigned long idadeInfo;
    gps1.f_get_position(&latitude, &longitude, &idadeInfo);   //O método f_get_position é mais indicado para retornar as coordenadas em variáveis float, para não precisar fazer nenhum cálculo
    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
    }
    if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
    }
    if ( (latitude != TinyGPS::GPS_INVALID_F_ANGLE) && (longitude != TinyGPS::GPS_INVALID_F_ANGLE) ) {
    }
    if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
    }
    gps1.crack_datetime(&ano, &mes, &dia, &hora, &minuto, &segundo, &centesimo, &idadeInfo);
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
        float altitudeGPS;
        altitudeGPS = gps1.f_altitude();
        if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 1000000)) {
        }
        velocidade = gps1.f_speed_kmph();   //km/h
        unsigned long sentido;
        sentido = gps1.course();
        unsigned short satelites;
        unsigned long precisao;
        satelites = gps1.satellites();
        precisao =  gps1.hdop();
        if (satelites != TinyGPS::GPS_INVALID_SATELLITES) {
        }
        if (precisao != TinyGPS::GPS_INVALID_HDOP) {
        }
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
void montaTela() {//coluna,linha
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  lcd.setCursor(0, 0); lcd.print("Bloco");  lcd.setCursor(10, 0); lcd.print("    "); lcd.setCursor(17, 0); lcd.print(":");
  lcd.setCursor(0, 1); lcd.print("Agua");  lcd.setCursor(10, 2); lcd.print("Veloci");
  lcd.setCursor(0, 2); lcd.print("Cabine");
  // lcd.setCursor(10, 2); lcd.print("Limite");
  //lcd.setCursor(0, 3); lcd.print("Limite");
  //lcd.setCursor(10, 3); lcd.print("Diesel");
}
//////////////////////////////////////////////////////////////////////////////////////////
void valores() {
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  /////temperatura do bloco
  lcd.setCursor(6, 0); lcd.print("   ");
  if (bloco1 < 100) {
    lcd.setCursor(7, 0); lcd.print(bloco1, 0);
  } else {
    lcd.setCursor(6, 0); lcd.print(bloco1, 0);
  }
  /////temperatura da agua
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  lcd.setCursor(6, 1); lcd.print("   ");
  if (agua < 100) {
    lcd.setCursor(7, 1); lcd.print(agua, 0);
  } else {
    lcd.setCursor(6, 1); lcd.print(agua, 0);
  }
  /////temperatura da cabine
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  lcd.setCursor(6, 2); lcd.print("   ");
  lcd.setCursor(7, 2); lcd.print(cabineTemperatura, 0);
  //  lcd.setCursor(7, 3); lcd.print("  ");
  //  lcd.setCursor(7, 3); lcd.print(limiteTemperatura);
  /////Horario
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
  }
  //////velocidade
  timerWrite(timer, 0); //reseta o temporizador (alimenta o watchdog)
  lcd.setCursor(17, 2); lcd.print("   ");
  if (velocidade < 10) {
    lcd.setCursor(19, 2); lcd.print(velocidade, 0);
  } else if (velocidade < 100) {
    lcd.setCursor(18, 2); lcd.print(velocidade, 0);
  } else {
    lcd.setCursor(17, 2); lcd.print(velocidade, 0);
  }
  //////Limite de velocidade
  //  lcd.setCursor(17, 2); lcd.print("   ");
  //  if (limiteVelocidade < 10) {
  //    lcd.setCursor(19, 2); lcd.print(limiteVelocidade);
  //  } else if (limiteVelocidade < 100) {
  //    lcd.setCursor(18, 2); lcd.print(limiteVelocidade);
  //  } else {
  //    lcd.setCursor(17, 2); lcd.print(limiteVelocidade);
  //  }
  //////diesel
  //  lcd.setCursor(18, 3); lcd.print("  ");
  //  if (diesel < 10) {
  //    lcd.setCursor(19, 3); lcd.print(diesel);
  //  } else {
  //    lcd.setCursor(18, 3); lcd.print(diesel);
  //  }
  lcd.clear();
  lcd.setBacklight(1);
  lcd.noBlink();
  lcd.noCursor();
  lcd.home();

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
