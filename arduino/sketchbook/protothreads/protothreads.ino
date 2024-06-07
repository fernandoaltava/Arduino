#include <pt.h>
#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define BUTTON_PIN 5
// Declare 3 protothreads
static struct pt pt1, pt2, pt3;
// A primeira função de protothread para piscar o LED 1 a cada 1 segundo
static int protothreadBlinkLED1(struct pt *pt)
{
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while(1) {
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 1000);
    digitalWrite(LED_1_PIN, HIGH);
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 1000);
    digitalWrite(LED_1_PIN, LOW);
  }
  PT_END(pt);
}
// A segunda função de protothread para piscar o LED 2 a cada 0,5 segundo
static int protothreadBlinkLED2(struct pt *pt)
{
  static unsigned long lastTimeBlink = 0;
  PT_BEGIN(pt);
  while(1) {
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 500);
    digitalWrite(LED_2_PIN, HIGH);
    lastTimeBlink = millis();
    PT_WAIT_UNTIL(pt, millis() - lastTimeBlink > 500);
    digitalWrite(LED_2_PIN, LOW);
  }
  PT_END(pt);
}
// Terceira função de protothread para ligar o LED 3 se
// o botão é pressionado.
static int protothreadPushButton(struct pt *pt)
{
  static unsigned long lastTimeCheck = 0;
  PT_BEGIN(pt);
  while (1) {
    lastTimeCheck = millis();
    PT_WAIT_UNTIL(pt, digitalRead(BUTTON_PIN) == HIGH);
    digitalWrite(LED_3_PIN, HIGH);
    PT_WAIT_UNTIL(pt, digitalRead(BUTTON_PIN) == LOW);
    digitalWrite(LED_3_PIN, LOW);
  }
  PT_END(pt);
}
// Na configuração, defina todos os LEDs como SAÍDA, pressione o botão como ENTRADA e
// inicia todos os protothreads
void setup() {
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
}
// No loop, só precisamos chamar os protothreads um por um
void loop() {
  protothreadBlinkLED1(&pt1);
  protothreadBlinkLED2(&pt2);
  protothreadPushButton(&pt3);
}
