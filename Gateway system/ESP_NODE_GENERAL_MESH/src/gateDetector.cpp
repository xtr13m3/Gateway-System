#ifndef GATEDETECTOR_CPP
#define GATEDETECTOR_CPP

#include "gateDetector.h"

int MovDetector::measureDist(void){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long durSig = pulseIn(echo, HIGH);
  int objDist= durSig * 0.034 / 2;
  return objDist; 
}

void MovDetector::printDist(int distance){
  Serial.print("Distanc to object: ");
  Serial.println(distance);
}

#endif
