void setup() {
  // put your setup code here, to run once:
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(0, !digitalRead(0));
  digitalWrite(1, !digitalRead(1));
  digitalWrite(2, !digitalRead(2));
  digitalWrite(3, !digitalRead(3));
  digitalWrite(4, !digitalRead(4));
  digitalWrite(5, !digitalRead(5));
  delay(1000);
}
