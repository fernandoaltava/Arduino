#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h> //Biblioteca que permite chamar o seu modulo ESP8266 na sua rede pelo nome ao inves do IP.
#include <ESP8266HTTPUpdateServer.h> //Biblioteca que cria o servico de atualizacão via wifi (ou Over The Air - OTA)
//unsigned long ultimoAcessoHost = 0;
const char* host      = "esp8266"; //Nome que seu ESP8266 (ou NodeMCU) tera na rede
const char* ssid      = "Luana"; //Nome da rede wifi da sua casa
const char* password  = "40224022"; //Senha da rede wifi da sua casa
ESP8266HTTPUpdateServer atualizadorOTA; //Este e o objeto que permite atualizacao do programa via wifi (OTA)
ESP8266WebServer servidorWeb(80); //Servidor Web na porta 80
//Esta e a pagina enviada para o navegador de internet
String paginaWeb = ""
"<!DOCTYPE html><html><head><title>FAL Automacoes</title>"
"</head><body style='margin: 0px; padding: 0px;'>"
"<h1>Altava Controle</h1>"
"</body>"
"</script></html>";
//////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  InicializaPinos();
  InicializaWifi();
  InicializaMDNS();
  InicializaServicoAtualizacao();
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("1");
    delay(2000);
    InicializaWifi();
    Serial.println("2");
    delay(2000);
    InicializaMDNS();
    Serial.println("3");
    delay(2000);
  }
      servidorWeb.handleClient();
      Serial.println("4");
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void RecepcaoClienteWeb() {
  servidorWeb.send(200, "text/html", paginaWeb);
  Serial.println("5");
    delay(2000);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void InicializaServicoAtualizacao() {
  atualizadorOTA.setup(&servidorWeb);
  Serial.println("6");
    delay(2000);
  servidorWeb.begin();
  Serial.println("7");
    delay(2000);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void InicializaWifi() {
  WiFi.begin(ssid, password);
  Serial.println("8");
    delay(2000);
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.println("9");
    delay(2000);
  }
  servidorWeb.on("/", RecepcaoClienteWeb);
  Serial.println("10");
    delay(2000);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void InicializaMDNS() {
  Serial.println("11");
    delay(2000);
  if (!MDNS.begin(host)) {
    Serial.println("12");
    delay(2000);
    while (1) {
      Serial.println("13");
      delay(1000);
    }
  }
  MDNS.addService("http", "tcp", 80);
  Serial.println("14");
    delay(2000);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void InicializaPinos(){
Serial.println("15");
    delay(2000);
}
