/*
 * Existem três portas seriais no ESP conhecidas como U0UXD, U1UXD e U2UXD.
 *
 * U0UXD é usado para se comunicar com o ESP32 para programação e durante o reset/boot.
 * O U1UXD não é usado e pode ser usado para seus projetos. Algumas placas usam esta porta para acesso SPI Flash embora
 * O U2UXD não é usado e pode ser usado para seus projetos.
 *
*/
#include <TinyGPS.h>

TinyGPS gps1;

#define RXD2 16
#define TXD2 17

void setup() {
  // Observe que o formato para configurar uma porta serial é o seguinte: Serial2.begin(taxa de transmissão, protocolo, pino RX, pino TX);
  Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd está no pino: "+String(TX));
  Serial.println("Serial Rxd está no pino: "+String(RX));
     Serial.println("O GPS do Brincando com Ideias aguarda pelo sinal dos satelites...");

}

void loop() { //Escolha Serial1 ou Serial2 conforme necessário
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
  }
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
        Serial.print(latitude,6);
        Serial.print(",");
        Serial.println(longitude, 6);           
     }

     if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
        Serial.print("Idade da Informacao (ms): ");
        Serial.println(idadeInfo);
     }


     //Dia e Hora
     int ano;
     byte mes, dia, hora, minuto, segundo, centesimo;
     gps1.crack_datetime(&ano, &mes, &dia, &hora, &minuto, &segundo, &centesimo, &idadeInfo);

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
