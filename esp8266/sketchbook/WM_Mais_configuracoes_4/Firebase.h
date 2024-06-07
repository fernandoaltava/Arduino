#include <FirebaseESP8266.h>
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;

FirebaseData firebaseData;


/////////////////////////////////////////////////////////////////
void leChave(String chave, int porta) {
//  ESP.wdtFeed();//Zera a contagem do wdt que esta por volta de 8 segundos
//  yield();//Zera a contagem do wdt que esta por volta de 8 segundos
//  if (Firebase.getString(firebaseData, "/Controle/" + chave)) {
  if (Firebase.getString(firebaseData, "/Controle/" + String(inputname))) {
    String numero_fb = firebaseData.stringData();
    if (numero_fb != "1") {
//      ESP.wdtFeed();//Zera a contagem do wdt que esta por volta de 8 segundos
//      digitalWrite(porta, HIGH);//desligado
      digitalWrite(16, HIGH);//desligado
      Serial.println(numero_fb);
    } else {
//      ESP.wdtFeed();//Zera a contagem do wdt que esta por volta de 8 segundos
//      digitalWrite(porta, LOW);//ligado
      digitalWrite(16, LOW);//ligado
      Serial.println(numero_fb);
    }
  }
}
//////////
void escreveIntFireBase(String chave, int valor) {
//  ESP.wdtFeed();//Zera a contagem do wdt que esta por volta de 8 segundos
//  yield();//Zera a contagem do wdt que esta por volta de 8 segundos
//  if ((Firebase.setInt(firebaseData, "/Controle/" + chave, valor)) == true) //
  if ((Firebase.setInt(firebaseData, "/Controle/" + String(inputname), valor)) == true) //
    Serial.println("Enviado");
}
//////////
void escreveStringFireBase(String chave, String valor) {
//  ESP.wdtFeed();//Zera a contagem do wdt que esta por volta de 8 segundos
//  yield();//Zera a contagem do wdt que esta por volta de 8 segundos
//  if ((Firebase.setString(firebaseData, "/Controle/" + chave, valor)) == true) //
  if ((Firebase.setString(firebaseData, "/Controle/" + String(inputname), valor)) == true) //
    Serial.println("Enviado");
}
//////////
void leSlider1() {
//  ESP.wdtFeed();//Zera a contagem do wdt que esta por volta de 8 segundos
//  yield();//Zera a contagem do wdt que esta por volta de 8 segundos
  if (Firebase.getString(firebaseData, "/Controle/Slider1")) {
    String texto_fb = firebaseData.stringData();
    int myInt = texto_fb.toInt();
    myservo1.write(myInt);
    delay(15);
  }
}
//////////
void leSlider2() {
//  ESP.wdtFeed();//Zera a contagem do wdt que esta por volta de 8 segundos
//  yield();//Zera a contagem do wdt que esta por volta de 8 segundos
  if (Firebase.getString(firebaseData, "/Controle/Slider2")) {
    String texto_fb = firebaseData.stringData();
    int myInt = texto_fb.toInt();
    myservo2.write(myInt);
    delay(15);
  }
}
//////////
void leSlider3() {
//  ESP.wdtFeed();//Zera a contagem do wdt que esta por volta de 8 segundos
//  yield();//Zera a contagem do wdt que esta por volta de 8 segundos
  if (Firebase.getString(firebaseData, "/Controle/Slider3")) {
    String texto_fb = firebaseData.stringData();
    int myInt = texto_fb.toInt();
    myservo3.write(myInt);
    delay(15);
  }
}
//////////
