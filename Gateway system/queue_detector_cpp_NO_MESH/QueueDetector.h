#ifndef QUEUEDETECTOR_H
#define QUEUEDETECTOR_H

#include "Arduino.h"

#define TRIG 2
#define ECHO 5
#define LED 4
#define THRESHOLD 10000
#define DELAY_2 2
#define DELAY_10 10

class QueueDetector{
  private: 
    int trig;
    int echo;
    int led;
    long sigDuration;
    int distance;
    int qDetected = 0;
    unsigned long prevMillis;
    unsigned long trigMillis;
    unsigned long measMillis;

  public: 
  QueueDetector(int trig, int echo, int led)
  {
    this->trig = trig;
    this->echo = echo;
    this->led = led;

    pinMode(trig,  OUTPUT);
    pinMode(echo, INPUT);
    pinMode(led, OUTPUT);
  }
  
  void clearTrig(void);
  void ping(void);
  int measureDist(void);
  void printDist(int distance);
  void detectQueue(void);
};

#endif
