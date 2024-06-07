/* September 2016
este é um teste do temporizador de watchdog ESP8266 e ESP.wdtDisable(), ESP.wdtEnable(0), ESP.wdtEnable(time) e ESP.wdtFeed() 
que foram adicionados ao ESP.h abril de 2015
  referências:   https://github.com/esp8266/Arduino/blob/master/doc/reference.md#timing-and-delays  = basic ref
   https://github.com/esp8266/Arduino/blob/master/cores/esp8266/Esp.h  = note line 89 comment that timeout value is not implemented
   http://bbs.espressif.com/viewtopic.php?f=7&t=203 = says watchdog timeout is about 1 s...but see next reference!
   http://bbs.espressif.com/viewtopic.php?t=836 = implies software WDT resets after 3.2 s, and hardware WDT resets after 6 s
       in the example, not sure why it is necessary to feed the soft WDT after it is stopped (maybe that keeps the HW WDT from timing out?)
   http://internetofhomethings.com/homethings/?p=396 = suggests that timeout is about 5 s   
   https://github.com/esp8266/Arduino/issues/34  = May 5 test not valid since delay(10000) kicks WDT?
   https://github.com/esp8266/Arduino/issues/1532  = note Jan 29 comment re SPIFFS"

   https://github.com/esp8266/Arduino/blob/master/doc/boards.md#boot-messages-and-modes
   rst cause:2, boot mode:(3,6)
    cause:
      0    unknown
      1    normal boot
      2    reset pin
      3    software reset
      4    watchdog reset
    boot mode:(x,y)
     "o primeiro valor respeita a configuração dos pinos dos pinos 0, 2 e 15" <- não é padrão inglês
     Nota do DAE: embora o acima não seja totalmente claro, o "primeiro" valor (ou seja, x)
     parece ser o modo de inicialização (com base nos estados dos pinos GPIO):
     1= carregador de inicialização UART (se 15=0v, 0=0v, 2=3.3v)
     2 = esboço de inicialização, ou seja, flash SPI (se 15 = 0 v, 0 = 3,3 v, 2 = 3,3 v)
     3=Modo SDIO não usado para Arduino (15=3,3v, outros = não importa)
   
    number = ((GPIO15 << 2) | (GPIO0 << 1) | GPIO2), where 0 v = 0, and 3.3v = 1
   
    Number    GPIO15    GPIO0    GPIO2    Mode
      0      0V        0V        0V        Not valid
      1      0V        0V        3.3V      Uart
      2      0V        3.3V      0V        Not valid
      3      0V        3.3V      3.3V      Flash
      4      3.3V      0V        0V        SDIO
      5      3.3V      0V        3.3V      SDIO
      6      3.3V      3.3V      0V        SDIO
      7      3.3V      3.3V      3.3V      SDIO
   
     Nota do DAE: "number" parece ser o valor "second" (ou seja, y)
   
*/
#include <ESP.h>;
void setup(){
  Serial.begin(115200);
   Serial.println("wdt");
   test1(3200); // test1 falha aqui com "soft WDT reset" causa: 2, modo de inicialização: (1,6) <- causa 2 = pino de redefinição (??)
//   test2(10000);// test2 falha aqui com "wdt reset" causa:4, modo de inicialização:(1,6)
//   test3(20000);// executa sem reset
//   test4(5000); // test4 falha aqui com "soft WDT reset" causa: 2, modo de inicialização: (1,6) <- causa 2 = redefinir pino (??)
}

void loop() {
}

// teste1()deve acionar o reset do SW WDT
// se a duração do loop while for longa o suficiente  
// acima de 3100 ocorre o boot rst cause:2, boot mode:(3,6)
void test1(unsigned long testDuration){
  Serial.print("test1 "); Serial.print(testDuration); Serial.print(" ");
  unsigned long prevTime=millis();
  while (millis()-prevTime<testDuration) { ESP.wdtFeed();}
  Serial.println(" end1");
 
}

// teste2() já que SW WDT está desabilitado NÃO deve acionar o reset do SW WDT
// desde que a duração seja curta o suficiente
// mas se a duração for muito longa, o HW WDT será redefinido   
// acima de 8300 ocorre o boot rst cause:4, boot mode:(3,6)
void test2(unsigned long testDuration){
  Serial.print("test2 "); Serial.print(testDuration); Serial.print(" ");
 ESP.wdtDisable();
  unsigned long prevTime=millis();
  while (millis()-prevTime<testDuration) {}
  ESP.wdtEnable(0);
  Serial.println(" end2");
}

// teste3() igual ao test2(), mas teste para ver se alimentar o WDT impede o reset
// o tempo limite do HW WDT (como implícito na referência acima)
// acima de 8300 sem o ESP.wdtFeed() ocorre o boot rst cause:4, boot mode:(3,6)
void test3(unsigned long testDuration){
  Serial.print("test3 "); Serial.print(testDuration); Serial.print(" ");
  ESP.wdtDisable();
  unsigned long prevTime=millis();
  unsigned long prevTime2=prevTime;
  while (millis()-prevTime<testDuration) {   
    if (millis()-prevTime2>100){ // alimentar cada 100 ms
       prevTime2=millis();
       ESP.wdtFeed();
    }   
  }
  ESP.wdtEnable(0);
  Serial.println(" end3");
}

// teste4() desde que o valor de tempo limite não foi implementado
// se a duração for longa o suficiente, deve acionar o reset do WDT SW
// acima de 3200 ocorre o reset rst cause:2, boot mode:(3,6)
void test4(unsigned long testDuration){
  Serial.print("test4 "); Serial.print(testDuration); Serial.print(" ");
   ESP.wdtDisable();
  ESP.wdtEnable(0);
  unsigned long prevTime=millis();
  while (millis()-prevTime<testDuration) {}
   Serial.println(" end4");
}
