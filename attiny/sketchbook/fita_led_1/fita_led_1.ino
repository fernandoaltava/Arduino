#include <FastLED.h>
#define LED_PIN 5   //DEFINIMOS O PINO DIGITAL "5" DO ARDUINO PARA SER O NOSSO "DIN" DO MÓDULO WS2812
#define NUM_LEDS 200   // O NUMERO DE LEDs QUE TEM NA NOSSA "REGUA/TIRA" DE LEDs.
#define BRIGHTNESS 255   // AUMENTA OU DIMINUI A "VELOCIDADE" QUE OS LEDs MUDAM DE CORES (1 ~ 255).
#define LED_TYPE WS2812   // O MODELO DA NOSSA REGUA DE LEDs (PODERIA SER A WS2812B).
#define COLOR_ORDER GRB   // A ORDEM DAS CORES DA TIRA DE LEDs.
int pausa = 70;
CRGB leds[NUM_LEDS];
//#define UPDATES_PER_SECOND 60   //ATUALIZACAO DO DISPLAY DE LEDs EM 1 SEGUNDO.
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int a = 0;
void setup() {
  pinMode(1, OUTPUT);
  delay(3000);   //Atraso de segurança na inicialização
//  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
//  FastLED.setBrightness( BRIGHTNESS );//brilho
//  currentPalette = RainbowColors_p;   //PALHETA DE CORES SENDO UTILIZADA ATUALMENTE!
//  currentBlending = LINEARBLEND;
//  FastLED.clear();
//  apaga();
}

void loop() {
//  if (digitalRead(pulso) > 0) {
//    doisleds();
//    apaga();
//    doisleds();
//    apaga();

//  }

  digitalWrite(1, HIGH);
  delay(50);               // wait for a second
  digitalWrite(1, LOW);
  delay(50);

}

void barra() {
  int a = 0;
  for (a = 0 ; a < NUM_LEDS; a++ ) {
    leds[a] = CRGB::OrangeRed;
    FastLED.show();
    delay(pausa);
  }
}
void apaga() {
  int a = 0;
  for (a = 0 ; a < NUM_LEDS; a++ ) {
    leds[a] = CRGB::Black;
    FastLED.show();
    //delay(pausa-50);
  }
}
//////////////////
void ponto() {
  int a = 0;
  for (a = 0 ; a < NUM_LEDS; a++ ) {
    leds[a] = CRGB::OrangeRed;//OrangeRed;
    FastLED.show();
    delay(pausa);
    leds[a] = CRGB::Black;
  }
}
////////////////////
void doisleds() {
  int a = 0;
  int b = 0;
  int c = 0;
  for (a = 0 ; a < NUM_LEDS; a++ ) {
    leds[a] = CRGB::OrangeRed;//OrangeRed;
    leds[a + 1] = CRGB::OrangeRed;//OrangeRed;

    FastLED.show();
    delay(pausa);
    leds[b] = CRGB::Black;
    b = b + 1;
  }
}
///////////////
void tresleds() {
  int a = 0;
  int b = 0;
  int c = 0;
  for (a = 0 ; a < NUM_LEDS; a++ ) {
    leds[a] = CRGB::OrangeRed;//OrangeRed;
    leds[a + 1] = CRGB::OrangeRed;//OrangeRed;
    leds[a + 2] = CRGB::OrangeRed;//OrangeRed;

    FastLED.show();
    delay(pausa);
    leds[b] = CRGB::Black;
    b = b + 1;
    leds[b] = CRGB::Black;
  }
}
