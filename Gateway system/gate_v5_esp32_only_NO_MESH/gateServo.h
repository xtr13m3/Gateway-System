#ifndef GATESERVO_H
#define GATESERVO_H

#include "Arduino.h"

#define OPEN 30
#define CLOSED 6
#define SERVO 16

#define PWM_FREQ 50
#define PWM_CH 0
#define PWM_RES 8

class Gate{
  private:
    int fq, ch, res, pin;
    int dutyCycle;
  public:
    Gate(int fq, int ch, int res, int pin){
      this->fq = PWM_FREQ;
      this->ch = PWM_CH;
      this->res = PWM_RES;
      this->pin = SERVO;

      ledcSetup(ch, fq, res);
      ledcAttachPin(pin,ch);
    }

    void openGate(void);
    void closeGate(void);
};

#endif 
