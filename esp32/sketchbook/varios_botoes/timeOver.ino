/*
 *  COMPONENTE TIME OVER
*/

unsigned long currentTimeOver = 0;
int delayTimeOver = 1000;

/*
 *  Seta um novo valor para atualizar o tempo futuro já atualizando o tempo atual.
 *  newTime = (o tempo recebido deverá ser em milissegundos)
 *  isTime = true | false
*/
void prepareTimeOver(int newTime,boolean isTime){
  delayTimeOver = newTime;
  if(isTime){
    setCurrentTimeOver();
  }
}

/*
 *  Seta um novo valor para atualizar o tempo futuro
 *  (o tempo recebido deverá ser em milissegundos)
*/
void prepareTimeOver(int newTime){
  delayTimeOver = newTime;
}

/*
 *  Utiliza como tempo o valor definido na inicialização
*/
void prepareTimeOver(){}

/*
 *  Atualiza o Tempo Corrido para o tempo futuro
*/
void setCurrentTimeOver(){
   currentTimeOver = millis() + delayTimeOver;
}

/*
 * Retorno o valor atual do tempo corrido.
*/
unsigned long getCurrentTimeOver(){
   return currentTimeOver;
}

/*
 * Retorna se o parâmetro informado na inicialização passou
 * @return true | false
*/
boolean monitoringTimeOver(){
  if(timeIsOver(currentTimeOver)){
    setCurrentTimeOver();
    return true;    
  }
  return false;
}

/*
 * Retorna se o tempo informado no parâmetro passou.
 * @return true | false
*/
boolean timeIsOver(unsigned long time){
  return (millis() > time) ? true : false;
}
