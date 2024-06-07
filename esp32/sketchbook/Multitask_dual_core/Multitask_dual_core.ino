TaskHandle_t Task1;
TaskHandle_t Task2;
// LED pins
const int led1 = 17;
const int led2 = 16;
////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  /////////////////////////////////////////
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
    Task1code,   /* Função da Task. */
    "Task1",     /* Nome da Task. */
    10000,       /* Tamanho da pilha da Task */
    NULL,        /* Parametro da Task */
    1,           /* Prioridade da Task */
    &Task1,      /* Identificador para acompanhar a Task */
    0);          /* Nucleo onde a Task vai rodar */
  //  delay(500);
  /////////////////////////////////////////
  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
    Task2code,   /* Função da Task. */
    "Task2",     /* Nome da Task. */
    10000,       /* Tamanho da pilha da Task */
    NULL,        /* Parametro da Task */
    1,           /* Prioridade da Task */
    &Task2,      /* Identificador para acompanhar a Task */
    1);          /* Nucleo onde a Task vai rodar */
  //    delay(500);
  /////////////////////////////////////////
}
////////////////////////////////////////////
////////////////////////////////////////////
void loop() {
}
