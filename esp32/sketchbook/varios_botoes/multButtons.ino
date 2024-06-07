/*
 * COMPONENTE MLTI BUTTONS
 * Utiliza Serial
*/
                                // 0 1 2 3
const byte PORT_MULTI_BUTTONS[] = {2,3,4,5};
#define SIZEOF_MULTI_BUTTONS   sizeof(PORT_MULTI_BUTTONS)/sizeof(byte)
boolean pressedMultiButton[SIZEOF_MULTI_BUTTONS];

/*
 *  Preparando o sistema
*/
void prepareMultiButton(){
    for(byte x = 0; x < SIZEOF_MULTI_BUTTONS; x++){
      pinMode(PORT_MULTI_BUTTONS[x], INPUT_PULLUP); 
    }
}

/*
 * Monitora as portas configuras no componente identificando um clique
 * @return int
*/
int monitoringMultiButton(){
   for(byte x = 0; x < SIZEOF_MULTI_BUTTONS; x++){
      if(digitalRead(PORT_MULTI_BUTTONS[x]) == LOW && pressedMultiButton[x] == false){
        delay(40);
          if(digitalRead(PORT_MULTI_BUTTONS[x]) == LOW) {
              // Ação a ser executada após o clique
              pressedMultiButton[x] = true;
              return x;
          }
      }else{
        if(digitalRead(PORT_MULTI_BUTTONS[x]) == HIGH && pressedMultiButton[x] == true) {
          pressedMultiButton[x] = false; 
        }
      }
   }
   return -1;
}

/*
 *  Evento de Test
*/
void testMultiButton(){
    switch(monitoringMultiButton()){
      case 0 :
            Serial.println("Clicou no botao 0");
      break;
      case 1 :
            Serial.println("Clicou no botao 1");
      break;
      case 2 :
            Serial.println("Clicou no botao 2");
      break;
      case 3 :
            Serial.println("Clicou no botao 3");
      break;
    }
}

/*
 *  Função Customizada
 *  
*/
void customMultiButton(){
  switch(monitoringMultiButton()){
      case 0 :
            // Ação a ser controlada
      break;
    }
}
