const int ledPin =  LED_BUILTIN;// the number of the LED pin
void setup()
{
  pinMode(ledPin, OUTPUT);//Define o LED Onboard como saida.
  digitalWrite(ledPin, 1);//Apaga o LED.
  delay(2000);//Espera 2 segundos para visualizarmos que o ESP foi iniciado.
 // ESP.wdtDisable();//Desabilita o SW WDT.

  for (long x = 0; x < 20; x++)//Ira piscar o LED 10x com intervalo de 250mS.
  {
    digitalWrite(ledPin, !digitalRead(ledPin));//Inverte o estado do LED.
    delayMicroseconds(500000);//Espera 250mS sw wdt
    //delay(1000);//hd wdt
    //yield();//Efetua o feed do SW WDT.
   // ESP.wdtFeed();//Alimenta o Watchdog.
  }
  //Após piscar 10x sem erros, irá entrar no loop e o LED começara a piscar
  // rapidamente indicando que não ocorreu erros.
  //Este código não efetua o FEED do SW WDT dentro do FOR, e ocasionara no
  // reset do ESP, então nunca irá piscar rapidamente, desde que não irá para o loop.
}
void loop()
{
  digitalWrite(ledPin, !digitalRead(ledPin));
  //delay(50);
  delayMicroseconds(550000);
  
  //ESP.wdtFeed();//Alimenta o HW WDT.
}
