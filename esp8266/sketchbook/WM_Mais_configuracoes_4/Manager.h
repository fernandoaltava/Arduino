/////////////////////////////////////////////////////////////////////////////////////////////
///   Declaração de Parametros ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
/// Nota: Inicializar parametros //////////////////////////////
char char_server_emoncms[40] = "serveremoncms.com";
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
const char* ssid_apmode = "ESP_Altava";
///////////////////////////////////////
//flag para salvar dados
bool shouldSaveConfig = false;
bool initialConfig = false;
bool parameterOK = false;
//retorno de chamada notificando-nos da necessidade de salvar a configuração
void saveConfigCallback () {
  Serial.println("Deve salvar a configuração");
  shouldSaveConfig = true;
}

void mont_FS() {
  if (SPIFFS.begin()) {///1
    Serial.println("sistema de arquivo montado");
    if (SPIFFS.exists("/config.json")) {///2
      //arquivo existe, lendo e carregando
      Serial.println("lendo arquivo de configuração");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {///3
        Serial.println("abrindo arquivo de configuração");
        size_t size = configFile.size();
        // Alocar um buffer para armazenar o conteúdo do arquivo.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        //json.printTo(Serial);
        /////debug json parametros
        if (json.success()) {///4
          Serial.println("\analisando json");
          strcpy(char_server_emoncms, json["char_server_emoncms"]);
          strcpy(char_port_emoncms, json["char_port_emoncms"]);
          strcpy(char_apikey_emoncms, json["char_apikey_emoncms"]);
          strcpy(char_updatedata_emoncms, json["char_updatedata_emoncms"]);
          strcpy(char_input_emoncms, json["char_input_emoncms"]);
          strcpy(char_node_emoncms, json["char_node_emoncms"]);
        }///4
        else {///5
          Serial.println("falha ao carregar configuração json");
        }///5
      }///3
    }///2
  }///1
  else {
    Serial.println("falha ao montarFS");
  }
}


void tela1() {
  // Os parâmetros extras a serem configurados (podem ser globais ou apenas na configuração)
  // Depois de conectar, parameter.getValue () obterá o valor configurado
  // id / nome espaço reservado / comprimento padrão do prompt
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  WiFiManagerParameter custom_server_emoncms("char_server_emoncms", "Firebase URL", char_server_emoncms, 40,
      "title= \"Parameter 1: server or Host Emoncms example: 192.168.0.12 or domainemoncms.com\"");//FIREBASE URL

  WiFiManagerParameter custom_port_emoncms("char_port_emoncms", "Pino", char_port_emoncms, 4,
      "title= \"Parameter 2: Port 80 default \"   type=\"number\"  ,  min=\"1\" max=\"9999\"   ");//PINO TIPO NUMERO DE 1 A 9999

  WiFiManagerParameter custom_apikey_emoncms("char_apikey_emoncms", "Firebase Secret Key", char_apikey_emoncms, 33,
      " type= password  maxlength=\"32\"  title= \"Parameter:3 Apikey Write Emoncms  example: 4ccb0b337dd7fa4b71f4601758e7f469\"    ");

  WiFiManagerParameter custom_updatedata_emoncms("char_updatedata_emoncms", "update", char_updatedata_emoncms, 4,
      "title= \"Parameter:4  Delay(sec) Time to send data to emoncms    example: 120\"   min=\"10\" max=\"9999\"   \"");

  WiFiManagerParameter custom_input_emoncms("char_input_emoncms", "input", char_input_emoncms, 20,
      "title= \"Parameter:5 Input Name in Emoncms  example: Temperature or Volt or Watts or Presure etc...\"   maxlength=\"20\"  \"");

  WiFiManagerParameter custom_node_emoncms("char_node_emoncms", "node", char_node_emoncms, 4,
      "title= \" Parameter:6   Node or group data example:10\"    type=\"number\" , min=\"1\" max=\"9999\"   ");

  WiFiManager wifiManager;
  /////////  definir configuração salvar notificar retorno de chamada //////////////////////////
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  //adicione todos os seus parâmetros aqui
  //////Agrega campos de parametros a Wifimanager  ////////////////////////////////
  //wifiManager.setDebugOutput(false); AQUI É O POSICIONAMENTO DAS VARIAVEIS NA TELA
  WiFiManagerParameter custom_text0("<p><strong> ESP8266 FAL Configuration </p> </strong>");
  wifiManager.addParameter(&custom_text0);
  wifiManager.addParameter(&custom_server_emoncms);
  wifiManager.addParameter(&custom_apikey_emoncms);
  wifiManager.addParameter(&custom_port_emoncms);
  wifiManager.addParameter(&custom_updatedata_emoncms);
  wifiManager.addParameter(&custom_input_emoncms);
  wifiManager.addParameter(&custom_node_emoncms);
  WiFiManagerParameter custom_text1("<H3><center><strong> FAL Automações </H3></center></strong>");//parametro de tela x
  wifiManager.addParameter(&custom_text1);//parametro de tela x
  ///////////////////////////////// /WiFiManager //////////////////////////////////////////////////////////////////////////////////////
  // Inicialização local. Assim que pagina estiver concluída, não há necessidade de mantê-la rodandoe
  // redefinir as configurações - para teste
  wifiManager.resetSettings();
  // define o tempo limite até que o portal de configuração seja desligado
  // útil para fazer tudo tentar novamente ou parar tempo em segundos
  wifiManager.setTimeout(280);
  // inicia um ponto de acesso com o nome especificado
  // aqui "AutoConnectAP"
  // e entra em um loop de bloqueio aguardando configuração
  // SEM ISSO, O AP NÃO PARECE FUNCIONAR CORRETAMENTE COM O SDK 1.5, atualize para pelo menos 1.5.1
  //WiFi.mode(WIFI_STA);
  //////////////  Aqui você cria a rede para a configuração   ////////////////////
  //adicionamos ao SSID o ID único e exclusivo de cada ESP
  String ssid = String(ssid_apmode) + String(ESP.getChipId());
  if (!wifiManager.startConfigPortal( ssid.c_str(), "12345678" )) {///x2
    Serial.println("Falha ao conectar atingiu o tempo limite");
    delay(3000);
    //reinicie e tente novamente, ou talvez coloque-o em sono profundo
    ESP.reset();
    delay(5000);
  }///x2
  strcpy(char_server_emoncms, custom_server_emoncms.getValue());
  strcpy(char_port_emoncms, custom_port_emoncms.getValue());
  strcpy(char_apikey_emoncms, custom_apikey_emoncms.getValue());
  strcpy(char_updatedata_emoncms, custom_updatedata_emoncms.getValue());
  strcpy(char_input_emoncms, custom_input_emoncms.getValue());
  strcpy(char_node_emoncms, custom_node_emoncms.getValue());

}

void tela2() {
  //////////////////////////////fim botão de configuração WIFI/////////////////////////////////////////////
  //////////////////////Grava Parametros JSON ///////////////////
  if (shouldSaveConfig) {///x3
    Serial.println("Salvando configuração");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["char_server_emoncms"] = char_server_emoncms;
    json["char_port_emoncms"] = char_port_emoncms;
    json["char_apikey_emoncms"] = char_apikey_emoncms;
    json["char_updatedata_emoncms"] = char_updatedata_emoncms;
    json["char_input_emoncms"] = char_input_emoncms;
    json["char_node_emoncms"] = char_node_emoncms;
    //    File configFile = SPIFFS.open("/config.json", "w");
    //    if (!configFile) {
    //      Serial.println("failed to open config file for writing");
    //    }
    json.printTo(Serial);
    //    json.printTo(configFile);
    //    configFile.close();
    //end save
  }///x3
  //////////////////////////////////////////////////////////////////////////////////////
  Serial.println("SSID Now");
  Serial.println(WiFi.SSID());
  ////////// Verificação de conexão ///////////////////////
  if (WiFi.SSID() == "") {///x4
    Serial.println("Não esta configurado!!! ou não conecta a REDE!!!");
    initialConfig = true;
  }///x4
  else {///x5
    Serial.println("Configuração WiFi correta");
    ////    digitalWrite(pin_led_Wifi, LOW);
    Serial.println("Parametros");
    ///// debug serial ///////////////////
    Serial.println(char_server_emoncms);
    Serial.println(char_port_emoncms);
    Serial.println(char_apikey_emoncms);
    Serial.println(char_updatedata_emoncms);
    Serial.println(char_input_emoncms);
    Serial.println(char_node_emoncms);
    // delay(2000);
    /////// converter parâmetros em variáveis para conexão com emoncms ////
    host = char_server_emoncms;//firebase url
    Serial.print("Host   ");
    Serial.println(host);
    port =  String (char_port_emoncms).toInt();////////////////////
    Serial.print("Porta   ");
    Serial.println(port);
    apikey = char_apikey_emoncms;
    Serial.print("Apikey   ");
    Serial.println(apikey);
    updatedata = String (char_updatedata_emoncms).toInt();
    Serial.print("Updatedata   ");
    Serial.println(updatedata);
    inputname = char_input_emoncms;
    Serial.print("Input name   ");
    Serial.println(inputname);
    nodedata = String (char_node_emoncms).toInt();
    Serial.print("Nodedata   ");
    Serial.println(nodedata);

    pinMode(port, OUTPUT);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////// operação que valida que não há parâmetros char * vazio !!! ///////
    if ( String(host).length()  ||  String(apikey).length() ||  String(inputname).length() ) {///x6
      parameterOK = true;
    }///x6
    else {///x7
      Serial.println("campos de parametros vazios");
      parameterOK = false;
    }///x7
    /// no caso de carregar 0 para dados atualizados, carregue 240s
    if (updatedata == 0) {///x8
      updatedata = 240;
    }///x8
    //////////////////////////////////////////////////////////////
  }///x5
}
