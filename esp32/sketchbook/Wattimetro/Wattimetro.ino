#include "EmonLib.h" 
 
EnergyMonitor emon1;
 
//Tensao da rede eletrica
int rede = 127.0;
 
//Pino do sensor SCT
int pino_sct = 1;
 
void setup() 
{
  Serial.begin(9600);   
  //Pino, calibracao - Cur Const= Ratio/BurdenR. 1800/62 = 29. 
  emon1.current(pino_sct, 29);
 Serial.println("Inicio ");
} 
  
void loop() 
{ 
  //Calcula a corrente  
  double Irms = emon1.calcIrms(1480);
  //Mostra o valor da corrente
  Serial.print("Corrente : ");
  Serial.print(Irms); // Irms
  Serial.print(" A "); 
  //Calcula e mostra o valor da potencia
  Serial.print(" Potencia : ");
  Serial.print(Irms*rede);
  Serial.println(" W ");   
  delay(1000);
}
