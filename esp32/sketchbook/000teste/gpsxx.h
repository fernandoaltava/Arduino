void converteHora();
void gpsxx() {
  while (Serial2.available()) {
    char cIn = Serial2.read();
    recebido = (gps1.encode(cIn) || recebido);  //Verifica até receber o primeiro sinal dos satelites
  }//fim do while (Serial2.available())
  if ( (recebido) && ((millis() - delayPrint) > 1000) ) {  //Mostra apenas após receber o primeiro sinal. Após o primeiro sinal, mostra a cada segundo.
    delayPrint = millis();
    //    SerialBT.println("                 GPS3");
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
    if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
      Serial.print("Idade da Informacao (ms): ");
      Serial.println(idadeInfo);
    }
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
    //altitude
    altitudeGPS = gps1.f_altitude();
    if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 1000000)) {
      Serial.print("Altitude (cm): ");
      Serial.println(altitudeGPS);
    }
    //velocidade
    velocidade1 = gps1.f_speed_kmph();   //km/h
    velocidade = (velocidade1, 0);
    Serial.print("Velocidade (km/h): ");
    Serial.println(velocidade1, 2);  //Conversão de Nós para Km/h
    Serial.print("Velocidade (km/h): ");
    Serial.println(velocidade1, 0);  //Conversão de Nós para Km/h
    //sentido (em centesima de graus)
    sentido = gps1.course();
    Serial.print("Sentido (grau): ");
    Serial.println(float(sentido) / 100, 2);
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
    //float distancia_entre;
    //distancia_entre = gps1.distance_between(lat1, long1, lat2, long2);
    //float sentido_para;
    //sentido_para = gps1.course_to(lat1, long1, lat2, long2);
  }//fim do if ( (recebido) && ((millis() - delayPrint) > 1000) )
}//fim do gpsxx
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
    default: {
      }
  }//fim do switch (hora)
}
