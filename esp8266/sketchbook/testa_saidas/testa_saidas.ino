int tempo;
void setup() {
  // put your setup code here, to run once:
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, INPUT);
  pinMode(14, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  pinMode(15, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(2)>0)pisca(50);
if(digitalRead(14)>0)pisca(300);
if(digitalRead(12)<1)pisca(500);
if(digitalRead(13)>0)pisca(700);
if(digitalRead(15)>0)pisca(1000);
  
}  
void pisca(int tempo){  
  digitalWrite(16, 1);
  delay(tempo);
  digitalWrite(5, 1);
  delay(tempo);
  digitalWrite(4, 1);
  delay(tempo);
  digitalWrite(0, 1);
  delay(tempo);
  digitalWrite(16, 0);
  delay(tempo);
  digitalWrite(5, 0);
  delay(tempo);
  digitalWrite(4, 0);
  delay(tempo);
  digitalWrite(0, 0);
  delay(tempo);

}
