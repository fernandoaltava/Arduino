/****************************************************************************************************************************
  SimplePut.ino - Simple Arduino web server sample
  
  For RTL8720DN, RTL8722DM and RTL8722CSM WiFi shields

  WiFiWebServer_RTL8720 is a library for the RTL8720DN, RTL8722DM and RTL8722CSM WiFi shields to run WebServer

  Built by Khoi Hoang https://github.com/khoih-prog/WiFiWebServer_RTL8720
  Licensed under MIT license

  Simple PUT client for HttpClient
  Connects to server once every five seconds, sends a PUT request
  and a request body

  created 14 Feb 2016
  modified 22 Jan 2019
  by Tom Igoe
 *****************************************************************************************************************************/

#include "defines.h"

char serverAddress[] = "192.168.2.112";  // server address
int port = 8080;

WiFiClient      client;
WiFiHttpClient  httpClient(client, serverAddress, port);

int status = WL_IDLE_STATUS;     // the Wifi radio's status

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  // you're connected now, so print out the data
  Serial.print(F("You're connected to the network, IP = "));
  Serial.println(WiFi.localIP());

  Serial.print(F("SSID: "));
  Serial.print(WiFi.SSID());

  // print the received signal strength:
  int32_t rssi = WiFi.RSSI();
  Serial.print(F(", Signal strength (RSSI):"));
  Serial.print(rssi);
  Serial.println(F(" dBm"));
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.print(F("\nStarting SimplePut on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(WIFI_WEBSERVER_RTL8720_VERSION);

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();

  Serial.print("Current Firmware Version = "); Serial.println(fv);
  
  if (fv != LATEST_RTL8720_FIRMWARE) 
  {
    Serial.println("Please upgrade the firmware");
  }
  
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to SSID: "); Serial.println(ssid);
    
    // Connect to WPA/WPA2 network. 2.4G and 5G are all OK
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data
  printWifiStatus();
}

void loop() {
  Serial.println("making PUT request");
  String contentType = "application/x-www-form-urlencoded";
  String putData = "name=light&age=46";

  httpClient.put("/", contentType, putData);

  // read the status code and body of the response
  int statusCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  Serial.println("Wait five seconds");
  delay(5000);
}
