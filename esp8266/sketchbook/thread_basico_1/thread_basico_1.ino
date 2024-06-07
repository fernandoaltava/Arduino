#include <Thread.h>
#include <ThreadController.h>
void piscaLed1(){
}
void piscaLed2(){
}
ThreadController cpu;
Thread threadDoLed1;
Thread threadDoLed2;

void setup(){
  threadDoLed1.setInterval(500);
  threadDoLed1.onRun(piscaLed1);
  threadDoLed2.setInterval(300);
  threadDoLed2.onRun(piscaLed2);
  cpu.add(&threadDoLed1);
  cpu.add(&threadDoLed2);
}
void loop(){
  cpu.run();
}
