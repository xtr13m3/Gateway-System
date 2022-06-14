#ifndef GATEDETECTOR_H
#define GATEDETECTOR_H

#include "Arduino.h"

#define TRIG_1 33
#define ECHO_1 34
#define TRIG_2 32
#define ECHO_2 35
#define LED_1 23
#define LED_2 19
#define DELAY_2 2
#define DELAY_10 10

#define MAX_DISTANCE 200

class MovDetector{
  private:
    int trig, echo, led, distance;
    unsigned long prevMillis, trigMillis, measMillis;
    long sigDuration;

  public:
    MovDetector(int trig, int echo, int led){
      this->trig = trig;
      this->echo = echo;
      this->led = led;

      pinMode(trig, OUTPUT);
      pinMode(echo, INPUT);
      pinMode(led, OUTPUT);
    }
    
      int measureDist(void);
      void printDist(int distance);
};


#endif
