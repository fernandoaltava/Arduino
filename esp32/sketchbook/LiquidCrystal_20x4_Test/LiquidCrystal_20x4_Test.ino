#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
int temp,comb,vel,lim = 0;
bool oleo,bat,ven1,ven2 = 0;
String oleo1,bat1,ven11,ven21;

void tela();
void valores();
void sensores();

void setup()
{
  int error;
  Serial.begin(115200);
  Serial.println("LCD...");
  // wait on Serial to be available on Leonardo
  while (!Serial)
    ;
  Serial.println("Dose: check for LCD");
  // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");
    lcd.begin(20, 4); // initialize the lcd

  } else {
    Serial.println(": LCD not found.");
  } // if
  lcd.noBlink();

  lcd.noCursor();
//temp=120;
//comb=80;
//vel=120;
//lim=60;

} // setup()


void loop()
{
  temp=random(130);
  comb=random(80);
  vel=random(130);
  lim=random(130);
  lcd.setBacklight(255);
  lcd.home();
  //lcd.clear();

  sensores();
  tela();
  valores();
  delay(500);
}
void valores(){
  lcd.setCursor(5, 0); lcd.print("   ");
  lcd.setCursor(5, 0); lcd.print(temp);
  lcd.setCursor(16, 0); lcd.print("  ");
  lcd.setCursor(16, 0); lcd.print(comb);
  lcd.setCursor(6, 1); lcd.print("   "); 
  lcd.setCursor(6, 1); lcd.print(oleo1); 
  lcd.setCursor(17, 1); lcd.print("   ");  
  lcd.setCursor(17, 1); lcd.print(bat1);  
  lcd.setCursor(6, 2); lcd.print("   ");  
  lcd.setCursor(6, 2); lcd.print(ven11);  
  lcd.setCursor(17, 2); lcd.print("   "); 
  lcd.setCursor(17, 2); lcd.print(ven21); 
  lcd.setCursor(4, 3); lcd.print("   ");
  lcd.setCursor(4, 3); lcd.print(vel);
  lcd.setCursor(15, 3); lcd.print("   ");
  lcd.setCursor(15, 3); lcd.print(lim);
  
}
void sensores(){
if(oleo==0)oleo1="OFF";
if(oleo==1)oleo1="ON";
if(bat==0)bat1="OFF";
if(bat==1)bat1="ON";
if(ven1==0)ven11="OFF";
if(ven1==1)ven11="ON";
if(ven2==0)ven21="OFF";
if(ven2==1)ven21="ON";
}

void tela() {
  lcd.setCursor(0, 0); lcd.print("Temp");  lcd.setCursor(8, 0);  lcd.print("C");
  lcd.setCursor(10, 0); lcd.print("Comb");  lcd.setCursor(19, 0);  lcd.print("L");
  lcd.setCursor(0, 1); lcd.print("Oleo");
  lcd.setCursor(10, 1); lcd.print("Bat");
  lcd.setCursor(0, 2); lcd.print("Ven1");
  lcd.setCursor(10, 2); lcd.print("Ven2");
  lcd.setCursor(0, 3); lcd.print("Vel");  lcd.setCursor(7, 3); lcd.print("Km");
  lcd.setCursor(10, 3); lcd.print("Lim");  lcd.setCursor(18, 3); lcd.print("Km");
}


/*
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Hello LCD");
    lcd.cursor();
    lcd.blink();
    lcd.noBlink();
    lcd.noCursor();
    lcd.noDisplay();
    lcd.setCursor(0, 0);
    lcd.scrollDisplayLeft();
    lcd.scrollDisplayRight();
*/
