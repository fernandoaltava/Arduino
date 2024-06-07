// Biblioteca do watchdog
//#include <esp_task_wdt.h>

//#define bot   4



void setup() {
  ESP.wdtDisable();
  Serial.begin(9600);
  pinMode(D4, OUTPUT);
  Serial.println("----------------------------------------");
  Serial.println("Esp Inicializado");
  ESP.wdtEnable(1000);
}

void loop() {
 // ESP.wdtFeed();
  while (true) {
    digitalWrite(D4,1);
    //delay(50);
    //digitalWrite(D4,0);
    //delay(50);
  //Serial.println(millis());
  }


  
}
