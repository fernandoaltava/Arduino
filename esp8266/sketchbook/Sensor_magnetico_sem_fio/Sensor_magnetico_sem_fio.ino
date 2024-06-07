/*
  No UNO o pino 2 refere-se à interrupção 0
  No NODEMCU o pino D3, GPIO 0 refere-se à interrupção 0
*/
#include <RCSwitch.h>
long a;
RCSwitch mySwitch = RCSwitch();
void setup() {
  pinMode(D0, OUTPUT);
  Serial.begin(9600);
  mySwitch.enableReceive(0);  //interrupção 0
  Serial.println("");
  Serial.println(" Inicio ");
  delay(200);
}
void loop() {
  if (mySwitch.available()) {
    a = mySwitch.getReceivedValue();
    Serial.print("Received ");
    Serial.print( mySwitch.getReceivedValue() );//id do sensor
    Serial.print(" / ");
    Serial.print( mySwitch.getReceivedBitlength() );//tamanho do id
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( mySwitch.getReceivedProtocol() );//número do protocolo
    mySwitch.resetAvailable();
    if (a==173920405||a==155991349||a==155991317||a==155991333||a==173920421) digitalWrite(D0, !digitalRead(D0));
  }
}
