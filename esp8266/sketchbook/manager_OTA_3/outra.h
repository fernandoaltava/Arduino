#include <ESP8266WiFi.h>//ota
#include <ArduinoOTA.h> //ota
#include <ESP8266mDNS.h>//ota
#include <WiFiManager.h>//manager
#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WebServer.h>     ///https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer
#include <DNSServer.h>
char char_server_emoncms[40]="serveremoncms.com";
char char_port_emoncms[4] = "80";
char char_apikey_emoncms[33] = "****************************";
char char_updatedata_emoncms[4] = "60";
char char_input_emoncms[20] = "variable_name";
char char_node_emoncms[4] = "1";
const char* host;
int port; 
const char* apikey;
int updatedata; 
const char* inputname;
int nodedata;
const char* ssid_apmode = "ESP_emoncms";
//flag for saving data
bool shouldSaveConfig = false;
bool initialConfig = false;
bool parameterOK = false;
//callback notifying us of the need to save config
WiFiManager wm1;void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
void x1() {
  Serial.println("mounting FS...");
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
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
}

void x2() {
  if ( digitalRead(5) == HIGH ) {
    //digitalWrite(pin_led_Wifi, HIGH);
    WiFiManagerParameter custom_server_emoncms    ("char_server_emoncms", "Firebase URL", char_server_emoncms, 40, "title= \"Parameter 1: server or Host Emoncms example: 192.168.0.12 or domainemoncms.com\"");
    WiFiManagerParameter custom_port_emoncms      ("char_port_emoncms", "Firebase Secret Key", char_port_emoncms, 4,       "title= \"Parameter 2: Port 80 default \"   type=\"number\"  ,  min=\"10\" max=\"9999\"   ");
    WiFiManagerParameter custom_apikey_emoncms    ("char_apikey_emoncms", "apikey write", char_apikey_emoncms, 33,  " type= password  maxlength=\"32\"  title= \"Parameter:3 Apikey Write Emoncms  example: 4ccb0b337dd7fa4b71f4601758e7f469\"    ");
    WiFiManagerParameter custom_updatedata_emoncms("char_updatedata_emoncms", "update", char_updatedata_emoncms, 4,  "title= \"Parameter:4  Delay(sec) Time to send data to emoncms    example: 120\"   min=\"10\" max=\"9999\"   \"");
    WiFiManagerParameter custom_input_emoncms     ("char_input_emoncms", "input", char_input_emoncms, 20,            "title= \"Parameter:5 Input Name in Emoncms  example: Temperature or Volt or Watts or Presure etc...\"   maxlength=\"20\"  \"");
    WiFiManagerParameter custom_node_emoncms      ("char_node_emoncms", "node", char_node_emoncms, 4,                "title= \" Parameter:6   Node or group data example:10\"    type=\"number\" , min=\"1\" max=\"9999\"   ");
//    WiFiManager wifiManager;
    wm1.setSaveConfigCallback(saveConfigCallback);
    WiFiManagerParameter custom_text0("<p><strong> ESP8266 Emoncms Configuration </p> </strong>");
    wm1.addParameter(&custom_text0);
    wm1.addParameter(&custom_server_emoncms);
    wm1.addParameter(&custom_port_emoncms);
    wm1.addParameter(&custom_apikey_emoncms);
    wm1.addParameter(&custom_updatedata_emoncms);
    wm1.addParameter(&custom_input_emoncms);
    wm1.addParameter(&custom_node_emoncms);
    WiFiManagerParameter custom_text1("<H3><center><strong> FAL Automações </H3></center></strong>");
    wm1.addParameter(&custom_text1);
    //wifiManager.resetSettings();
    wm1.setTimeout(280);
    String ssid = String(ssid_apmode) + String(ESP.getChipId());
    if (!wm1.startConfigPortal( ssid.c_str() )) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
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
}

void x3() {
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
  }
}
  void x4() {
    Serial.println("SSID Now");
    Serial.println(WiFi.SSID());
    if (WiFi.SSID() == "") {
      Serial.println("No esta configurado!!! o no conecta a la RED!!!");
      Serial.println("Not configured !!! or do not connect to the NETWORK !!!");
      initialConfig = true;
    } else {
      Serial.println("Configuracion correcta");
      Serial.println ("Wifi Configuration Correct");
      digitalWrite(pin_led_Wifi, LOW);
      Serial.println("Parameters");
      Serial.println(char_server_emoncms);
      Serial.println(char_port_emoncms);
      Serial.println(char_apikey_emoncms);
      Serial.println(char_updatedata_emoncms);
      Serial.println(char_input_emoncms);
      Serial.println(char_node_emoncms);
      host = char_server_emoncms;
      port =  String (char_port_emoncms).toInt();
      apikey = char_apikey_emoncms;
      updatedata = String (char_updatedata_emoncms).toInt();
      inputname = char_input_emoncms;
      nodedata = String (char_node_emoncms).toInt();
      if ( String(host).length()  ||  String(apikey).length() ||  String(inputname).length() ) {
        parameterOK = true;
      }
      else {
        Serial.println("campos de parametros vacios");
        Serial.println("empty parameter fields");
        parameterOK = false;
      }
      if (updatedata == 0) {
        updatedata = 240;
      }
    }
  }
}
