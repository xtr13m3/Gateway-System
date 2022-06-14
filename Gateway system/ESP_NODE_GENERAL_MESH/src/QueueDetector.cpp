#ifndef QUEUEDETECTOR_CPP
#define QUEUEDETECTOR_CPP

#include "QueueDetector.h"

void QueueDetector::clearTrig(void){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
}

void QueueDetector::ping(void){
//  if(micros() - trigMillis > DELAY_2)
//  {
//    trigMillis = micros();
    digitalWrite(trig, HIGH);
      delayMicroseconds(10);
//  }
//  if(micros() - trigMillis > DELAY_10){
//    trigMillis = micros();
      digitalWrite(trig, LOW); 
//  }
}

int QueueDetector::measureDist(void){
  if(millis() - measMillis > 5000)
  {
      clearTrig();
      ping();
      long durSig = pulseIn(echo, HIGH);
      int objDist= durSig * 0.034 / 2;
      return objDist; 
  }
  
}

void QueueDetector::printDist(int distance){
  Serial.print("Distanc to object: ");
  Serial.println(distance);
}


int QueueDetector::detectQueue(void){

  distance = measureDist();
  printDist(distance);
  
  if(millis() - prevMillis > THRESHOLD){
    prevMillis = millis();

    if(qDetected == 0){
      if(distance <= 100)
      {
        qDetected = 1;
        digitalWrite(LED, HIGH);
        return 1;
      }
    }
    else if(qDetected == 1)
    {
            if(distance > 100)
      {
        qDetected = 0;
        digitalWrite(LED, LOW);
        return 0;
      }
    }
  }
}

#endif
