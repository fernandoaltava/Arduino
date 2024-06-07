#include <OneWire.h>    //////////////////////TEMP SENSOR SECTION
#include <DallasTemperature.h>
//#include <Adafruit_GFX.h>//////////////////////OLED SECTION
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4//////////////////////////////OLED 
Adafruit_SSD1306 display(OLED_RESET);
#define ONE_WIRE_BUS 2////////////////////temp signal wire coonected to 8 D/PIN
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float Celcius = 0;
int mi = 82; //temp 82
int ma = 87; //temp 87
int t = 0;
void setup(void)
{
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  pinMode(3, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);///// Call the begin function of the display object by passing our I2C address 0x3C
  Serial.begin(9600);
  sensors.begin();
  display.clearDisplay();/////////////clears the display completely.
  display.setTextSize(2);/////////accepts an integer number as a size. The greater the number, the bigger the text would be. Smallest size is 1 which is the default size //of texts.
  display.setTextColor(WHITE);///////////////specify the color using display.setTextColor() WHITE/BLACK
  display.setCursor(0, 8);//////////////////specify where on the display we're going to display the text.
  display.println("ALTAVA");////////////We draw something on by calling on our (display) object,
  display.display();//////////////////Call the display.display() function to make the actual drawing happen on the hardware level.
  display.startscrollright(0x00, 0x0F);
  delay(1500);
  display.startscrollleft(0x00, 0x0F);
  delay(1500);
  display.clearDisplay();
  display.stopscroll();
}
void temperatura()
{
  sensors.requestTemperatures();///////////////getting the actual temperature value.
  Celcius = sensors.getTempCByIndex(0);//////////get the temperature in Celsius.we’re using just one sensor its index is 0.
  t = Celcius;
  //////////////////////////////////////////////If you have more than one sensor, you use index 0 for the ///first sensor, index 1 for the second sensor, and so on.
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Temperatura     ");
  display.println(Celcius);
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(30, 14);
  display.print(t);//Celcius);
  display.println("  C");
  display.drawCircle (72, 15, 2, WHITE);
  if (Celcius < mi) {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
    display.invertDisplay(false);
  }
  if (Celcius >= mi ) {
    display.invertDisplay(true);
    digitalWrite(12, LOW);//ventoinha 1
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.println("1ON");
  } else {
    digitalWrite(12, HIGH);
  }
  if (Celcius >= ma) {
    display.invertDisplay(true);
    digitalWrite(13, LOW);//ventoinha 2
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.println("2ON");
  } else {
    digitalWrite(13, HIGH);
  }
  /////////////////////////////////////////////////////////////////////////////////
  display.drawLine(0, 8, 128, 8, WHITE);
  display.drawLine (110, 10, 110, 22, WHITE);
  display.drawLine (114, 10, 114, 22, WHITE);
  display.drawLine (110, 10, 114, 10, WHITE);
  display.drawCircle (112, 25, 3, WHITE);
  display.drawCircle (112, 25, 4, WHITE);
  display.drawPixel (112, 12, WHITE);
  display.drawPixel (112, 14, WHITE);
  display.drawPixel (112, 16, WHITE);
  display.drawPixel (112, 18, WHITE);
  display.drawPixel (112, 20, WHITE);
  display.display();
}
void combustivel()
{
  sensors.requestTemperatures();///////////////getting the actual temperature value.
  Celcius = sensors.getTempCByIndex(0);//////////get the temperature in Celsius.we’re using just one sensor its index is 0.
  t = Celcius;
  //////////////////////////////////////////////If you have more than one sensor, you use index 0 for the ///first sensor, index 1 for the second sensor, and so on.
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Combustivel");
  display.setCursor(90, 0);
  display.setTextSize(1);
  display.println(t);//Celcius);
  display.setTextSize(2);
  display.setTextColor(WHITE, BLACK);
  display.setCursor(30, 14);
  int x = map(analogRead(A0), 0, 1023, 0, 80);
  display.println(x);
  if (x < 10) {
    display.fillCircle (12, 20, 5, WHITE);
    //    digitalWrite(11, HIGH);
  }// else {
  //    digitalWrite(11, LOW);
  //  }
  if (Celcius < mi) {
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);
  }
  if (Celcius >= mi ) {
    digitalWrite(12, LOW);//ventoinha 1
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.println("1ON");
  } else {
    digitalWrite(12, HIGH);
  }
  if (Celcius >= ma) {
    digitalWrite(13, LOW);//ventoinha 2
    display.setCursor(0, 20);
    display.setTextSize(1);
    display.println("2ON");
  } else {
    digitalWrite(13, HIGH);
  }
  /////////////////////////////////////////////////////////////////////////////////
  int a = 97;
  int b = 12;
  display.drawLine(0, 8, 128, 8, WHITE);//linha
  display.drawRoundRect(a, b, 18, 20, 2, WHITE);
  display.drawLine (a + 4, b + 4, a + 12, b + 4, WHITE);
  display.drawLine (a + 4, b + 6, a + 12, b + 6, WHITE);
  display.drawLine (a + 4, b + 8, a + 12, b + 8, WHITE);
  display.drawLine (a - 1, b + 19, a + 18, b + 19, WHITE);
  display.drawPixel (a + 20, b + 11, WHITE);
  display.drawPixel (a + 21, b + 11, WHITE);
  display.drawPixel (a + 22, b + 11, WHITE);
  display.drawPixel (a + 23, b + 11, WHITE);
  display.drawPixel (a + 24, b + 11, WHITE);
  display.drawPixel (a + 24, b + 12, WHITE);
  display.drawPixel (a + 24, b + 13, WHITE);
  display.drawPixel (a + 24, b + 14, WHITE);
  display.drawPixel (a + 24, b + 15, WHITE);
  display.drawPixel (a + 25, b + 15, WHITE);
  display.drawPixel (a + 26, b + 15, WHITE);
  display.drawPixel (a + 27, b + 15, WHITE);
  display.drawPixel (a + 28, b + 15, WHITE);
  display.drawPixel (a + 28, b + 14, WHITE);
  display.drawPixel (a + 28, b + 13, WHITE);
  display.drawPixel (a + 28, b + 12, WHITE);
  display.drawPixel (a + 28, b + 11, WHITE);
  display.drawRoundRect(a + 27, b + 4, 4, 8, 2, WHITE);
  display.drawLine (a + 27, b + 4, a + 23, b + 1, WHITE);
  display.display();
}
void loop()
{
  //  while (digitalRead(3) > 0) {
  //    temperatura();
  //  }
  temperatura();//delay(500);
  //combustivel();//delay(500);
}
