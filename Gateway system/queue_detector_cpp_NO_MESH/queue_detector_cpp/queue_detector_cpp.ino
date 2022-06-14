#include "QueueDetector.h"

QueueDetector QD = QueueDetector(TRIG,ECHO,LED);  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  QD.detectQueue();
}
