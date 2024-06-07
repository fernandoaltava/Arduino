#include <OneWire.h>    //////////////////////TEMP SENSOR SECTION
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2////////////////////temp signal wire coonected to 8 D/PIN
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float
kp = 50,  //constante proporcional
ki = 0.1, //constante integral
kd = 0.1, //constante derivada
p = 0, p2 = 0, //controle proporcional
i = 0, i2 = 0, //controle integral
d = 0, d2 = 0, //controle derivativo
pid = 0, pid2 = 0, //controle proporcional, integral e derivativo (PID)
erro, erro2,    //variavel de erro
tdecorrido = 0,  //variavel de tempo decorrido para iniciar o loop de controle
setpoint = 27,   //temperatura alvo
setpoint2 = 30,
temperatura;     //temperatura medida


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensors.begin();
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);

}

void loop() {
  sensors.requestTemperatures();///////////////getting the actual temperature value.
  temperatura = sensors.getTempCByIndex(0);//////////get the temperature in Celsius.we’re using just one sensor its index is 0.

  erro = setpoint - temperatura;
  erro2 = setpoint2 - temperatura;
  float delta = (millis() - tdecorrido) / 1000.0;
  tdecorrido = millis();
  //controle proporcional
  p = kp * erro;
  p2 = kp * erro2;
  //controle integral
  i += (ki * erro) * delta;
  i2 += (ki * erro2) * delta;
  //controle derivativo
  d = erro * kd / delta;
  d2 = erro2 * kd / delta;
  //PID
  pid = p + i + d;
  pid2 = p2 + i2 + d2;
  //controles de fato
  if (pid > 0) {
//    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
  }
  else {
//    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
  }
  if (pid2 > 0) {
    digitalWrite(13, HIGH);
//    digitalWrite(12, HIGH);
  }
  else {
    digitalWrite(13, LOW);
//    digitalWrite(12, LOW);
  }

  
  Serial.print("p = kp*erro -> ");
  Serial.println(p);

  Serial.print("i += (ki * erro) * delta -> ");
  Serial.println(i);

  Serial.print("d = erro * kd / delta -> ");
  Serial.println(d);

  Serial.print("pid = p + i + d ->                 ");
  Serial.println(pid);

  Serial.print("p2 = kp*erro2 -> ");
  Serial.println(p2);

  Serial.print("i2 += (ki * erro2) * delta -> ");
  Serial.println(i2);

  Serial.print("d2 = erro2 * kd / delta -> ");
  Serial.println(d2);

  Serial.print("pid2 = p2 + i2 + d2 ->             ");
  Serial.println(pid2);

  Serial.print("temperatura -> ");
  Serial.println(temperatura);

}
