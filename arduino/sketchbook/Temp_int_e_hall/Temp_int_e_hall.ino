/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP32     //
// Website: Easycoding.tn      //
/////////////////////////////////


#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

void setup()
{
Serial.begin(9600);

}


void loop()
{

    Serial.print("Temperatura interna ");
    Serial.print(((temprature_sens_read() - 32 ) / 1.8));
    Serial.println(" °C");
    delay(1000);
    Serial.print("Sensor Hall ");
    Serial.println((hallRead()));
    delay(1000);

}
