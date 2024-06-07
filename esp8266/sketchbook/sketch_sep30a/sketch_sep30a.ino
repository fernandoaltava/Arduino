#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
const char *ssid     = "Luana2";
const char *password = "40224022";
const long utcOffsetInSeconds = -10800;     //UTC offset in seconds
char days[7][12]  = {"DOM", "SEG", "TER", "QUA", "QUI", "SEX", "SAB"};
char month[12][4] = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);            //create object of NTP client
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(800);
    Serial.print (".");
  }
  timeClient.begin();
}
void loop() 
{
  timeClient.update();          //upadte time
  displayTimeDate();             //display time on OLED
  delay(100);
}
void displayTimeDate(){
  String meridiem;
  int hour;
  /*Calculate time and date*/
  unsigned long epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epochTime);
  int date = ptm->tm_mday;
  int monthNum = ptm->tm_mon+1;
  int year = ptm->tm_year+1900;
  String day = days[timeClient.getDay()];
  int minute = timeClient.getMinutes();
  int second = timeClient.getSeconds();
  /*Convert 24hr format to 12hr format*/
  if(timeClient.getHours() >= 12){
    meridiem = "PM"; 
    hour = timeClient.getHours() - 12;
  }else{
    meridiem = "AM";
    hour = timeClient.getHours();
  }
  if(hour == 0){
    hour = 12;
  }
  Serial.print(day);
  Serial.print(" ");
  if(date < 10) Serial.print(0);
  Serial.print(date);
  Serial.print("/");
  Serial.print(month[monthNum-1]);
  Serial.println(year);
  if(hour < 10) Serial.print(0);
  Serial.print(hour);
  Serial.print(":");
  if(minute < 10) Serial.print(0);
  Serial.print(minute);
  Serial.print(":");
  if(second < 10) Serial.print(0);
  Serial.print(second);
  Serial.print(" ");
  Serial.println(meridiem);
}
