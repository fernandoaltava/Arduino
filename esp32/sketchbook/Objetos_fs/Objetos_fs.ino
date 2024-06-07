#include "FS.h"
#include "SPIFFS.h"
#define FORMAT_SPIFFS_IF_FAILED true
void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
void readFile(fs::FS &fs, const char * path);
void writeFile(fs::FS &fs, const char * path, const char * message);
void appendFile(fs::FS &fs, const char * path, const char * message);
void renameFile(fs::FS &fs, const char * path1, const char * path2);
void deleteFile(fs::FS &fs, const char * path);
void testFileIO(fs::FS &fs, const char * path);
////////////////////////////////////////////////////////////////////////////
void setup(){
    Serial.begin(115200);
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    listDir(SPIFFS, "/", 0);delay(1000);
//    writeFile(SPIFFS, "/Telemetria.txt", "100.00;desligado;10.0;1.20;200;100;300;ligado;ligado;ligado");
//    writeFile(SPIFFS, "/Telemetria.txt", "100.00;desligado;10.0;1.20;200;100;300;ligado;ligado;ligado");
//    appendFile(SPIFFS, "/hello.txt", "World1!\r\n");delay(1000);
//    appendFile(SPIFFS, "/hello.txt", "World2!\r\n");delay(1000);
//    appendFile(SPIFFS, "/hello.txt", "World3!\r\n");delay(1000);
//    appendFile(SPIFFS, "/hello.txt", "World4!\r\n");delay(1000);
//    deleteFile(SPIFFS, "/hello.txt");
    readFile(SPIFFS, "/Telemetria.txt");delay(2000);
//    renameFile(SPIFFS, "/hello.txt", "/foo.txt");
//    readFile(SPIFFS, "/foo.txt");
//    deleteFile(SPIFFS, "/foo.txt");
//    testFileIO(SPIFFS, "/test.txt");
//    deleteFile(SPIFFS, "/test.txt");
    Serial.println( "Test complete" );
}
/////////////////////////////////////////////////////////////////////////////////
void loop(){

}
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listando Diretório: %s\r\n", dirname);
    File root = fs.open(dirname);
    if(!root){
        Serial.println("- falhou ao abrir diretorio");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - não há diretorio");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}
////////////////////////////////////////////////////////////////
void readFile(fs::FS &fs, const char * path){
    Serial.printf("Lendo arquivo: %s\r\n", path);
    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- falha ao abrir arquivo para leitura");
        return;
    }
    Serial.println("- lendo arquivo:");//read from file:");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}
////////////////////////////////////////////////////////////////////////
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- falha ao abrir arquivo para escrita");
        return;
    }
    if(file.print(message)){
        Serial.println("- escrevendo no arquivo");
    } else {
        Serial.println("- falha ao escrever");
    }
    file.close();
}
///////////////////////////////////////////////////////////////////////////
void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\r\n", path);
    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("- falha ao abrir o arquivo para acrescentar dados");
        return;
    }
    if(file.print(message)){
        Serial.println("- menssagem acrescentada");
    } else {
        Serial.println("- falha ao acrescentar");
    }
    file.close();
}
//////////////////////////////////////////////////////////////////////////
void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\r\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("- arquivo renomeado");
    } else {
        Serial.println("- falha ao renomear");
    }
}
////////////////////////////////////////////////////////
void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- arquivo deletado");
    } else {
        Serial.println("- falha ao deletar");
    }
}
///////////////////////////////////////////////////////////////
void testFileIO(fs::FS &fs, const char * path){
    Serial.printf("Testing file I/O with %s\r\n", path);
    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- falha ao abrir arquivo para gravação");
        return;
    }
    size_t i;
    Serial.print("- escrevendo" );
    uint32_t start = millis();
    for(i=0; i<2048; i++){
        if ((i & 0x001F) == 0x001F){
          Serial.print(".");
        }
        file.write(buf, 512);
    }
    Serial.println("");
    uint32_t end = millis() - start;
    Serial.printf(" - %u bytes escritos em in %u ms\r\n", 2048 * 512, end);
    file.close();
    file = fs.open(path);
    start = millis();
    end = start;
    i = 0;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        Serial.print("- lendo" );
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F){
              Serial.print(".");
            }
            len -= toRead;
        }
        Serial.println("");
        end = millis() - start;
        Serial.printf("- %u bytes lidos em %u ms\r\n", flen, end);
        file.close();
    } else {
        Serial.println("- falha ao abrir arquivo para leitura");
    }
}
