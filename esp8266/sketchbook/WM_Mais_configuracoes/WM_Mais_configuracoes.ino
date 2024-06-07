
/*--------------------------------------------------------------
  Program:       WifiManger Parameters Emoncms Temperature

  Description:  Configuration and parameterization of ESP8266 with WifiManager 
                library for sending data to IoT platform Emoncms (OpenEnergymonitor).
                Available Parameters:
                -emoncms server or host
                -port
                -apikey
                -date update time
                -Input Name
                -Node associated with input

                Configuracion y parametrizacion de ESP8266 con libreria WifiManager
                para envio de datos a plataforma IoT Emoncms (OpenEnergymonitor).
                Parametros Disponibles
                -servidor o host emoncms:
                -puerto
                -apikey
                -tiempo de actualizacion dato (delay) segundos
                -Nombre de input
                -Nodo asociado a input                
  
  Hardware:     ESP8266 12E NodeMCU Lolin. + Sensor DS18B20 (Onewire)
                
  Software:     Arduino IDE v1.8.3
  
  Date:         09 Oct 2017
   
  Created:  PDAControl   http://pdacontroles.com   http://pdacontrolen.com

  Based: Library WifiManager for tzapu   https://github.com/tzapu/WiFiManager

  Based:  libraries/ ESP8266WiFi/ examples /WifiClient   

  Emoncms Website:  https://openenergymonitor.org/  or  https://emoncms.org/
  
  
--------------------------------------------------------------*/


#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <ESP8266WebServer.h>     ///https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

 
#include <OneWire.h>             //https://github.com/PaulStoffregen/OneWire
#include <DallasTemperature.h>   ///https://github.com/milesburton/Arduino-Temperature-Control-Library
 
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2 // pin 2 
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS); 
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

/*

Para configurar ESP8266 con wifimanager:
1 Mantener presionado "button_config" asignado al pin D1 y pulsar el boton de reset de esp8266, 
  esperar que el led de pin_led_Wifi encienda.
2 conectarse a red ESP_###### 
3 ingresar a http://192.168.4.1
4 configurar y guardar.

To configure ESP8266 with wifimanager:
1 Hold down "button_config" assigned to pin D1 and press the reset button on esp8266,
 wait for the pin_led_Wifi led to light up.
2 connect to network ESP _ ######
3 enter http://192.168.4.1
4 set up and save.


*/

/////////////////////////////////////////////////////////////////////////////////////////////
///   Declaracion de Parametros - Declaration of Parameters  ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/// Nota: Inicializar parametros //////////////////// Note: Initialize parameters ////////// 


char char_server_emoncms[40]="serveremoncms.com";
char char_port_emoncms[4] = "80";
char char_apikey_emoncms[33] = "****************************";
char char_updatedata_emoncms[4] = "60";
char char_input_emoncms[20] = "variable_name";
char char_node_emoncms[4] = "1";

////////////////////////////////////////////////////////////////////////////////////////////

const char* host;
int port; 
const char* apikey;
int updatedata; 
const char* inputname;
int nodedata;

#define button_config  5  ///PIN D1 NodeMCU  /// Pulsador Normalmente Abierto // Normally Open Button
#define pin_led_Wifi  14 //led verde // green led 
#define pin_led_App   4  //led rojo // red led 

///////////////////////////

// SSID de red de configuracion WifiManager //
// SSID WifiManager configuration network //

const char* ssid_apmode = "ESP_emoncms";

///////////////////////////////////////

//flag for saving data
bool shouldSaveConfig = false;
bool initialConfig = false;
bool parameterOK = false;


//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("\n Starting"); 

    pinMode(button_config, INPUT_PULLUP);
  pinMode(pin_led_Wifi, OUTPUT);
  pinMode(pin_led_App, OUTPUT);

   sensors.begin();

///  Nota: importante reiniciar sistema SPIFFS al editar, modificar, o adicionar campos de parametros
///  clean FS, for testing
//   SPIFFS.format();
  
////////////////////////////////////////////
////////Montar SP///////////////////////////
////////////////////////////////////////////


  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        //json.printTo(Serial);                                              /////debug json parameters
        if (json.success()) {
          Serial.println("\nparsed json");        

        strcpy(char_server_emoncms, json["char_server_emoncms"]);
        strcpy(char_port_emoncms, json["char_port_emoncms"]);
        strcpy(char_apikey_emoncms, json["char_apikey_emoncms"]);
        strcpy(char_updatedata_emoncms, json["char_updatedata_emoncms"]);
        strcpy(char_input_emoncms, json["char_input_emoncms"]);
        strcpy(char_node_emoncms, json["char_node_emoncms"]);

          

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
  //end read

////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////


//  Pulsador Habilita configuracion WifiManager     Push button Enables WifiManager configuration   /////////////////
 // is configuration portal requested?
  if ( digitalRead(button_config) == HIGH ) {

    digitalWrite(pin_led_Wifi, HIGH);

  
  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
  WiFiManagerParameter custom_server_emoncms    ("char_server_emoncms", "Firebase URL", char_server_emoncms, 40,"title= \"Parameter 1: server or Host Emoncms example: 192.168.0.12 or domainemoncms.com\"");
////  WiFiManagerParameter custom_server_emoncms    ("char_server_emoncms", "server emoncms", char_server_emoncms, 40,"title= \"Parameter 1: server or Host Emoncms example: 192.168.0.12 or domainemoncms.com\"");
////  WiFiManagerParameter custom_port_emoncms      ("char_port_emoncms", "port emoncms", char_port_emoncms, 4,       "title= \"Parameter 2: Port 80 default \"   type=\"number\"  ,  min=\"10\" max=\"9999\"   ");
  WiFiManagerParameter custom_port_emoncms      ("char_port_emoncms", "Firebase Secret Key", char_port_emoncms, 4,       "title= \"Parameter 2: Port 80 default \"   type=\"number\"  ,  min=\"10\" max=\"9999\"   ");

  
  
  WiFiManagerParameter custom_apikey_emoncms    ("char_apikey_emoncms", "apikey write", char_apikey_emoncms, 33,  " type= password  maxlength=\"32\"  title= \"Parameter:3 Apikey Write Emoncms  example: 4ccb0b337dd7fa4b71f4601758e7f469\"    ");
  ///WiFiManagerParameter custom_apikey_emoncms    ("char_apikey_emoncms", "apikey write", char_apikey_emoncms, 34,"type= password");
  WiFiManagerParameter custom_updatedata_emoncms("char_updatedata_emoncms", "update", char_updatedata_emoncms, 4,  "title= \"Parameter:4  Delay(sec) Time to send data to emoncms    example: 120\"   min=\"10\" max=\"9999\"   \"");
  WiFiManagerParameter custom_input_emoncms     ("char_input_emoncms", "input", char_input_emoncms, 20,            "title= \"Parameter:5 Input Name in Emoncms  example: Temperature or Volt or Watts or Presure etc...\"   maxlength=\"20\"  \"");
  WiFiManagerParameter custom_node_emoncms      ("char_node_emoncms", "node", char_node_emoncms, 4,                "title= \" Parameter:6   Node or group data example:10\"    type=\"number\" , min=\"1\" max=\"9999\"   ");
  
  
 
  WiFiManager wifiManager;

  
    /////////  set config save notify callback //// notifica que se guardaran nuevos parametros //////////////////////////
  wifiManager.setSaveConfigCallback(saveConfigCallback);
   
  //add all your parameters here
 //////Agrega campos de parametros a Wifimanager  //// Adds parameter fields to Wifimanager ////////////////////////////
 
  //wifiManager.setDebugOutput(false);

  WiFiManagerParameter custom_text0("<p><strong> ESP8266 Emoncms Configuration </p> </strong>");
  wifiManager.addParameter(&custom_text0);

    
  wifiManager.addParameter(&custom_server_emoncms);    
  wifiManager.addParameter(&custom_port_emoncms);    
  wifiManager.addParameter(&custom_apikey_emoncms);
  wifiManager.addParameter(&custom_updatedata_emoncms);
  wifiManager.addParameter(&custom_input_emoncms);
  wifiManager.addParameter(&custom_node_emoncms);

  WiFiManagerParameter custom_text1("<H3><center><strong> FAL Automações </H3></center></strong>");

////  WiFiManagerParameter custom_text1("<H3><center><strong> More info: PDAControl </H3></center></strong>");
  wifiManager.addParameter(&custom_text1);  
////  WiFiManagerParameter custom_web("<a><center>English:  pdacontrolen.com</center></a><br>");
////  wifiManager.addParameter(&custom_web); 
////  WiFiManagerParameter custom_web1("<a><center>Espa&ntilde;ol: pdacontroles.com</center></a>");  
////  wifiManager.addParameter(&custom_web1);


///////////////////////////////// /WiFiManager //////////////////////////////////////////////////////////////////////////////////////
    //Local intialization. Once its business is done, there is no need to keep it around 

    //reset settings - for testing
    //wifiManager.resetSettings();

    //sets timeout until configuration portal gets turned off
    //useful to make it all retry or go to sleep
    //in seconds
    wifiManager.setTimeout(280);

    //it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration

    //WITHOUT THIS THE AP DOES NOT SEEM TO WORK PROPERLY WITH SDK 1.5 , update to at least 1.5.1
    //WiFi.mode(WIFI_STA);




//////////////  Aqui crea la red para la configuracion              //////////////////
//////////////  Here you create the network for the configuration  ////////////////////

    //agregamos al SSID el ID propio y unico de cada ESP
    //we add to the SSID the unique and unique ID of each ESP  

     String ssid = String(ssid_apmode) + String(ESP.getChipId());     

//    if (!wifiManager.startConfigPortal( ssid.c_str(),"password" )) {
    if (!wifiManager.startConfigPortal( ssid.c_str() )) {
      
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      delay(5000);
    }

  strcpy(char_server_emoncms, custom_server_emoncms.getValue());
  strcpy(char_port_emoncms, custom_port_emoncms.getValue());
  strcpy(char_apikey_emoncms, custom_apikey_emoncms.getValue());
  strcpy(char_updatedata_emoncms, custom_updatedata_emoncms.getValue());
  strcpy(char_input_emoncms, custom_input_emoncms.getValue());
  strcpy(char_node_emoncms, custom_node_emoncms.getValue());
    
  }
  //////////////////////////////fin - end   button configuration WIFI/////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////

  
//////////////////////Guarda Parametros JSON - Save Parameters JSON ///////////////////
///////////////////////////////////////////////////////////////////////////
  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();

       json["char_server_emoncms"] = char_server_emoncms;
       json["char_port_emoncms"] = char_port_emoncms;
       json["char_apikey_emoncms"] = char_apikey_emoncms;       
       json["char_updatedata_emoncms"] = char_updatedata_emoncms;
       json["char_input_emoncms"] = char_input_emoncms;
       json["char_node_emoncms"] = char_node_emoncms;


    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

  Serial.println("SSID Now");
  Serial.println(WiFi.SSID());

////////// Verificacion de Conexion - Connection Verification ///////////////////////
  if (WiFi.SSID() == "") {
    
              Serial.println("No esta configurado!!! o no conecta a la RED!!!");
              Serial.println("Not configured !!! or do not connect to the NETWORK !!!");
              initialConfig = true; 
                 
          }else{
        
             Serial.println("Configuracion correcta");     
        ///     Serial.println ("Wifi Configuration Correct");
             
              digitalWrite(pin_led_Wifi, LOW);
        
              Serial.println("Parameters");
        
              ///// debug serial ///////////////////
              Serial.println(char_server_emoncms);
              Serial.println(char_port_emoncms);
           //   Serial.println(char_apikey_emoncms);
              Serial.println(char_updatedata_emoncms);
              Serial.println(char_input_emoncms);
              Serial.println(char_node_emoncms);
              //////////////////////////////////////
             // delay(2000);      
              
              //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
              /// convertir parametros a variables para conexion con emoncms //// convert parameters to variables for connection to emoncms ////
              host = char_server_emoncms;
              port =  String (char_port_emoncms).toInt();
              apikey = char_apikey_emoncms;
              updatedata = String (char_updatedata_emoncms).toInt();
              inputname=char_input_emoncms;                             
              nodedata = String (char_node_emoncms).toInt();
            
              ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////          
          
        /////// operacion or que valida que no existan parametros char* vacios!!!      //////
        /////// operation that validates that there are no char * empty parameters !!! ///////
           
           if( String(host).length()  ||  String(apikey).length() ||  String(inputname).length() ){  
                  
               parameterOK = true;    
                
           }
              else{
                        
              Serial.println("campos de parametros vacios");
              Serial.println("empty parameter fields");
              parameterOK = false;        
            
            }
        
              /// en caso de cargar 0 a updatedata, cargar 240s
              /// in case of loading 0 to updatedata, load 240s
              
                if (updatedata==0){
                  updatedata=240;      
                }    
                 
////////////////////////////////////////////////////////////// 
  }
 //////////////////////end - fin (void setup) //////////////////////////////////////// 
}




void loop() { 



  if ((!initialConfig) && (parameterOK)) {  

                 // Logging data to cloud //
               // Serial.print("Connecting to ");
               // Serial.println(host);
                
                // Use WiFiClient class to create TCP connections
                WiFiClient client;
              
                if (!client.connect(host, port)) {
                 /// Serial.println("connection failed");    
                  
                   digitalWrite(pin_led_App, !digitalRead(pin_led_App));   /// Flashing leds
                   digitalWrite(pin_led_Wifi, !digitalRead(pin_led_Wifi)); /// Flashing leds
                 return;
                }else
                {
                  digitalWrite(pin_led_App, HIGH);
                  digitalWrite(pin_led_Wifi, LOW);
                }
              
                  
              ///   valores a envia envia a emoncms  ///
              ///   values to send sends to emoncms   ///  
                  
              ///   int value= random(0,1000); /// test value

              //// get temperature ds18b20  - capturar temperatura ds18b20   /// Onewire
                sensors.requestTemperatures();
               float celsius = sensors.getTempCByIndex(0);
               Serial.println(sensors.getTempCByIndex(0));               


              /// RSSI -esp8266              
                long rssi = WiFi.RSSI();   

             

              /// JSON/HTTP Emoncms
              Serial.println("json");
              String json ="/emoncms/input/post.json?node="+String(nodedata)+"&json={"+String(inputname)+":"+ String(celsius)+","+"RSSI:"+String(rssi)+"}&apikey="+apikey;
              Serial.println(json);
              Serial.println("");
                                         
                 // This will send the request to the server emoncms
              client.print(String("GET ") + json + " HTTP/1.1\r\n" +     
                              "Host: " + host + "\r\n" + 
                              "Connection: close\r\n\r\n");

              
                ///////////////// timeout 5 sec - sin respuesta de servidor.. //////////////////////
                 unsigned long timeout = millis();
                while (client.available() == 0) {
                  if (millis() - timeout > 5000) {
                    digitalWrite(pin_led_App, LOW);
                    Serial.println(">>> Client Timeout !");
                    client.stop();
                    return;
                  }
                }
                
                // Read all the lines of the reply from server and print them to Serial
                while(client.available()){
                  String line = client.readStringUntil('\r');
                  Serial.print(line);
                }
                
                Serial.println();
                Serial.println("closing connection");
              
                delay(updatedata*1000);    /// update data  sec * 1000ms   
              
           ////////////end void main/////////////


 
  
  }else
  {
         
          Serial.println("Conexion a red fallida");    
          Serial.println("Network connection failed");
          Serial.println("");
          Serial.println("configurar credenciales de red (boton Config + Boton Reset)");
          Serial.println("configure network credentials (Config button + Reset button)");
             
             delay(3000);
    
  }


}
