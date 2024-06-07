#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

int pos1 = 68;    // variable to store the servo position
int pos2 = 78;    // variable to store the servo position
void parado() {
  pos1 = 68;    // variable to store the servo position
  pos2 = 78;    // variable to store the servo position
  myservo1.write(pos1);//78 -ah   +h              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
  myservo2.write(pos2);//68              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
}
void frenteLento() {
  pos1 = 58;    // variable to store the servo position
  pos2 = 88;    // variable to store the servo position
  myservo1.write(pos1);//78 -ah   +h              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
  myservo2.write(pos2);//68              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
}
void frenteRapido() {
  pos1 = 0;    // variable to store the servo position
  pos2 = 180;    // variable to store the servo position
  myservo1.write(pos1);//78 -ah   +h              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
  myservo2.write(pos2);//68              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
}
void reLento() {
  pos1 = 78;    // variable to store the servo position
  pos2 = 68;    // variable to store the servo position
  myservo1.write(pos1);//78 -ah   +h              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
  myservo2.write(pos2);//68              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
}
void reRapido() {
  pos1 = 180;    // variable to store the servo position
  pos2 = 0;    // variable to store the servo position
  myservo1.write(pos1);//78 -ah   +h              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
  myservo2.write(pos2);//68              // tell servo to go to position in variable 'pos'
  delay(15);                       // waits 15ms for the servo to reach the position
}



void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(3);  // attaches the servo on pin 9 to the servo object
}

void loop() {
parado();
delay(2000);
frenteLento();
delay(2000);
frenteRapido();
delay(2000);
frenteLento();
delay(2000);
parado();
delay(2000);
reLento();
delay(2000);
reRapido();
delay(2000);
reLento();
delay(2000);
parado();
delay(2000);

}
