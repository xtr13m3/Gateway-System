#ifndef GATESERVO_CPP
#define GATESERVO_CPP

#include "gateServo.h"

void Gate::openGate(void){
  int dutyCycle = CLOSED;
  ledcWrite(PWM_CH, dutyCycle);
}

void Gate::closeGate(void){
  int dutyCycle = OPEN;
  ledcWrite(PWM_CH, dutyCycle);
}

#endif
