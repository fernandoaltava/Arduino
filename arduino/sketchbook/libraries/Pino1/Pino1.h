#include<Arduino.h>

#define Servo_VERSION           2     // software version of this library
#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minimum time to refresh servos in microseconds 
#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer 
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

class Pino1 {
public:
    Pino1(int pin);
    int pino;
    bool estado;
    bool teste = 0;
    long onTime;
    long offTime;
    long on;
    long off;
    int pinoState;
    unsigned long previousMillis = 0;
    void ligar();
    void desligar();
    void inverter();
    void piscar(long on);
    void pulsoA(long on, long off);
    void pulsoB(long off, long on);
///////////////////////////////
  uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
  uint8_t attach(int pin, int min, int max); // as above but also sets min and max values for writes. 
  void detach();
  void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
  void writeMicroseconds(int value); // Write pulse width in microseconds 
  int read();                        // returns current pulse width as an angle between 0 and 180 degrees
  int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
  bool attached();                   // return true if this servo is attached, otherwise false ////////////////////////////
///////////////////////////////
private:
   uint8_t servoIndex;               // index into the channel data for this servo
   int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH    
   int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH   




};
