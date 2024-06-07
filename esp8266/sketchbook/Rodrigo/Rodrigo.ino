#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define Rele1 0
#define Rele2 15
#define Rele3 2
#define Rele4 4

bool Estado_Do_Rele1 = LOW;
bool Estado_Do_Rele2 = LOW;
bool Estado_Do_Rele3 = LOW;
bool Estado_Do_Rele4 = LOW;

const char* ssid = "Recanto Reencontro";//"nome-da-rede";
const char* password = "40224022";//"senha-da-rede";
int LED = 2;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(Rele1, OUTPUT);
  pinMode(Rele2, OUTPUT);
  pinMode(Rele3, OUTPUT);
  pinMode(Rele4, OUTPUT);

  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // verifica e armazena se tem clientes conectados na rede

  if (client) { // se você conseguir um cliente,
    Serial.println("Novo Cliente."); // imprime uma mensagem pela porta serial
    String currentLine = ""; // faz uma String para manter os dados recebidos do cliente
    while (client.connected()) { // loop enquanto o cliente está conectado
      if (client.available()) { // se houver bytes para ler do cliente,
        char c = client.read(); // leia um byte e depois
        Serial.write(c); // imprima o monitor serial
        if (c == '\n') { // se o byte for um caractere de nova linha


          /* se a linha atual estiver em branco, você terá dois caracteres de nova linha em uma linha.
            esse é o fim da solicitação HTTP do cliente, então envie uma resposta: */
          if (currentLine.length() == 0) {
            /* Os cabeçalhos HTTP sempre começam com um código de resposta (por exemplo, HTTP / 1.1 200 OK)
              e um tipo de conteúdo para que o cliente saiba o que está por vir e, em seguida, uma linha em branco: */
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();


            // configuração de estilo do site
            client.print("<style type=\"text/css\"> a{margin: 50px 50px; background: #47963e; color: #ffffff; text-align: center; text-decoration: none; padding: 1% 20% 1%; border-radius: 10px; font-size: 5.0em;}</style>");
            // o conteúdo do cabeçalho HTTP
            client.print("<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' align='center'><h1><p align='center'> Teste de Automação Residencial </p></br></br> </h1>");

            client.print("<p align='center'><a href=\"/T1\">Garagem </a> </br></br></br> </p>");
            client.print("<p align='center'><a href=\"/T2\">Corredor </a> </br></br></br> </p>");
            client.print("<p align='center'><a href=\"/T3\">Quarto </a> </br></br></br> </p>");
            client.print("<p align='center'><a href=\"/T4\">Lavanderia </a> </br></br></br> </p>");

            // A resposta HTTP termina com outra linha em branco:
            client.println();
            // sair do loop while:
            break;
          } else { // se você tiver uma nova linha, então limpe a linha atual:
            currentLine = "";
          }
        } else if (c != '\r') { // se você tiver qualquer outra coisa além de um caractere de retorno de linha,
          currentLine += c; // adicioná-lo ao final da linha atual
        }

        // Verifica se o pedido do cliente foi para atualizar algum dos reles (GET /T)

        if (currentLine.endsWith("GET /T1")) {

          if (Estado_Do_Rele1 == LOW) {
            digitalWrite(Rele1, HIGH);
            Estado_Do_Rele1 = HIGH;
          } else {
            digitalWrite(Rele1, LOW);
            Estado_Do_Rele1 = LOW;
          }
        }
        if (currentLine.endsWith("GET /T2")) {

          if (Estado_Do_Rele2 == LOW) {
            digitalWrite(Rele2, HIGH);
            Estado_Do_Rele2 = HIGH;
          } else {
            digitalWrite(Rele2, LOW);
            Estado_Do_Rele2 = LOW;
          }
        }
        if (currentLine.endsWith("GET /T3")) {

          if (Estado_Do_Rele3 == LOW) {
            digitalWrite(Rele3, HIGH);
            Estado_Do_Rele3 = HIGH;
          } else {
            digitalWrite(Rele3, LOW);
            Estado_Do_Rele3 = LOW;
          }
        }
        if (currentLine.endsWith("GET /T4")) {

          if (Estado_Do_Rele4 == LOW) {
            digitalWrite(Rele4, HIGH);
            Estado_Do_Rele4 = HIGH;
          } else {
            digitalWrite(Rele4, LOW);
            Estado_Do_Rele4 = LOW;
          }
        }
      }
    }
  }
  // termina a conexão com o cliente
  client.stop();
  Serial.println("Cliente desconectado.");
}
