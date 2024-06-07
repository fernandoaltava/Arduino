// Touch screen library with X Y and Z (pressure) readings as well
// as oversampling to avoid 'bouncing'
// This demo code returns raw readings, public domain
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>

#include <stdint.h>
#include "TouchScreen.h"

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

int a, b, c, d = 0;
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A3  // must be an analog pin, use "An" notation!
#define YM 8   // can be a digital pin
#define XP 9   // can be a digital pin
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
int sensorPin15 = A15;    // select the input pin for the potentiometer
int sensorValue15 = 0;  // variable to store the value coming from the sensor

int sensorPin14 = A14;    // select the input pin for the potentiometer
int sensorValue14 = 0;  // variable to store the value coming from the sensor





uint16_t ID, oldcolor, currentcolor;
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup(void) {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Serial.println("Example: Font_simple");
  Serial.print("found ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
  tft.begin(ID);
  tft.setRotation(1);
  //  tft.fillRect(0, 80, 10, 10, BLUE);//linha1,coluna1,linha2,coluna2,cor
  a = 300;
  b = 200;
  c = 20;
  d = 20;
  tft.fillScreen(BLACK);
  emon1.current(14, 3.2);     
  //tft.setFont(5);
  //tft.setCursor(180, 1);
  //tft.setTextColor(GREEN);
  //tft.setTextSize(&FreeSevenSegNumFont);
  //tft.print("teste");
  //delay(2000);
}

void loop(void) {
  sensorValue15 = analogRead(sensorPin15);
  //sensorValue14 = analogRead(sensorPin14);
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  a=Irms;
  //char y[2];
  //String str;
  //str=String(a);
    tft.fillRect(230,  1, 60, 230, BLACK);//linha1,coluna1,linha2,coluna2,cor
  
  
  //tft.fillRect(0, 0, 310, 200, BLUE);//linha1,coluna1,linha2,coluna2,cor
  //delay(1000);
  //tft.fillScreen(BLACK);
  //showmsgXY(5, 100, 1, &FreeSevenSegNumFont, "012345678");
  showmsgXYtxt(  1, 20,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 1");//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  295, 20,  1, &FreeSerif12pt7b, BLUE, "W");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 20,  1, &FreeSerif12pt7b, RED, sensorValue15);//a);//"12345678901234567890123456"); //26 caracteres

  showmsgXYtxt(  1, 40,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 2");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 40,  1, &FreeSerif12pt7b, RED, Irms);//"12345678901234567890123456"); //26 caracteres

  showmsgXYtxt(  1, 60,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 3");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 60,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  1, 80,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 4");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 80,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  1, 100,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 5");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 100,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  1, 120,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 6");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 120,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  1, 140,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 7");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 140,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  1, 160,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 8");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 160,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  1, 180,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 9");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 180,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  1, 200,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 10");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 200,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres
  showmsgXYtxt(  1, 220,  1, &FreeSerif12pt7b, BLUE, "Valor sensor 11");//"12345678901234567890123456"); //26 caracteres
  showmsgXY(   230, 220,  1, &FreeSerif12pt7b, RED, a);//"12345678901234567890123456"); //26 caracteres

  /*  showmsgXY(1, 40, 1, &FreeSerif12pt7b, RED, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 60, 1, &FreeSerif12pt7b, GREEN, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 80, 1, &FreeSerif12pt7b, CYAN, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 100, 1, &FreeSerif12pt7b, MAGENTA, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 120, 1, &FreeSerif12pt7b, YELLOW, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 140, 1, &FreeSerif12pt7b, WHITE, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 160, 1, &FreeSerif12pt7b, BLUE, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 180, 1, &FreeSerif12pt7b, RED, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 200, 1, &FreeSerif12pt7b, GREEN, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 220, 1, &FreeSerif12pt7b, CYAN, "12345678901234567890123456"); //26 caracteres
    showmsgXY(1, 240, 1, &FreeSerif12pt7b, MAGENTA, "12345678901234567890123456"); //26 caracteres


    delay(1000);
    // tft.setFont(5);
    // tft.setCursor(180, 1);
    // tft.setTextColor(GREEN);
    // tft.setTextSize(&FreeSevenSegNumFont);
    // tft.print("teste");

  */
  //Serial.println(y);
  ////    tft.fillRect(50, 50, 75, 75, BLUE); //linha1,coluna1,linha2,coluna2,cor
  ////    tft.drawPixel(319, 239, GREEN);
  // a point object holds x y and z coordinates
  ////   TSPoint p = ts.getPoint();

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  ////   if (p.z > 10){//ts.pressureThreshhold) {
  ////   Serial.print("X = "); Serial.print(p.x);
  ////     Serial.print("\tY = "); Serial.print(p.y);
  ////     Serial.print("\tPressure = "); Serial.println(p.z);
  ////   }

  delay(100);
  a=a+1;
}


void showmsgXY(int x, int y, int sz, const GFXfont *f, const *cor, int msg)//const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  //    tft.drawFastHLine(0, y, tft.width(), WHITE);
  tft.setFont(f);
  tft.setCursor(x, y);
  //  tft.setTextColor(Blue);
  tft.setTextColor(cor);
  tft.setTextSize(sz);
  tft.print(msg);
  //delay(1000);
  //tft.fillScreen(BLACK);
}
void showmsgXYtxt(int x, int y, int sz, const GFXfont *f, const *cor, const char *msg)
{
  int16_t x1, y1;
  uint16_t wid, ht;
  //    tft.drawFastHLine(0, y, tft.width(), WHITE);
  tft.setFont(f);
  tft.setCursor(x, y);
  //  tft.setTextColor(Blue);
  tft.setTextColor(cor);
  tft.setTextSize(sz);
  tft.print(msg);
  //delay(1000);
  //tft.fillScreen(BLACK);
}
/*
  WriteCmdData  KEYWORD2
  begin KEYWORD2
  color565  KEYWORD2
  drawCircle  KEYWORD2
  drawFastHLine KEYWORD2
  drawFastVLine KEYWORD2
  drawLine  KEYWORD2
  drawPixel KEYWORD2
  drawRect  KEYWORD2
  drawRoundRect KEYWORD2
  fillCircle  KEYWORD2
  fillRect  KEYWORD2
  fillRoundRect KEYWORD2
  fillScreen  KEYWORD2
  height  KEYWORD2
  invertDisplay KEYWORD2
  pushColors  KEYWORD2
  readGRAM  KEYWORD2
  readID  KEYWORD2
  readPixel KEYWORD2
  readReg KEYWORD2
  readReg32 KEYWORD2
  reset KEYWORD2
  setAddrWindow KEYWORD2
  setCursor  KEYWORD2
  setRotation  KEYWORD2
  setTextColor  KEYWORD2
  setTextSize KEYWORD2
  vertScroll  KEYWORD2
  width KEYWORD2
*/
