#include "EmonLib.h"
EnergyMonitor SCT0131;
EnergyMonitor SCT0132;
EnergyMonitor SCT0133;
int pinSCT1 = A5;   //Pino analógico conectado ao SCT-013
int pinSCT2 = A4;   //Pino analógico conectado ao SCT-013
int pinSCT3 = A3;   //Pino analógico conectado ao SCT-013
int tensao = 127;
int potencia1,potencia2,potencia3;
void setup()
{
    SCT0131.current(pinSCT1, 6.0606);
    SCT0132.current(pinSCT2, 6.0606);
    SCT0133.current(pinSCT3, 6.0606);
    Serial.begin(9600);
}
void loop()
{
    double Irms1 = SCT0131.calcIrms(1480);   // Calcula o valor da Corrente
    double Irms2 = SCT0132.calcIrms(1480);   // Calcula o valor da Corrente
    double Irms3 = SCT0133.calcIrms(1480);   // Calcula o valor da Corrente
    
    potencia1 = Irms1 * tensao;          // Calcula o valor da Potencia Instantanea    
    potencia2 = Irms2 * tensao;          // Calcula o valor da Potencia Instantanea    
    potencia3 = Irms3 * tensao;          // Calcula o valor da Potencia Instantanea    

//    Serial.print("Corrente1 = ");
//    Serial.print(Irms1);
//    Serial.println(" A");
    Serial.print("Potencia1 = ");
    Serial.print(potencia1);
    Serial.print(" W   ");

//    Serial.print("Corrente2 = ");
//    Serial.print(Irms2);
//    Serial.println(" A");
    Serial.print("Potencia2 = ");
    Serial.print(potencia2);
    Serial.print(" W   ");

//    Serial.print("Corrente3 = ");
//    Serial.print(Irms3);
//    Serial.println(" A");
    Serial.print("Potencia3 = ");
    Serial.print(potencia3);
    Serial.println(" W");


   
    delay(500);
    Serial.println("");
}
