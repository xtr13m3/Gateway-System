#include "co2Sensor.h"
#include "Algorithm.h" 

CO2Sensor sens = CO2Sensor(MQ_PIN, LED);
Algorithm alg = Algorithm(CO2_P, AIR_INFL, MAX_PPM, MAX_OCCUP);

  unsigned long prevMill;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

//  Serial.println(sens.getRZero());
if(millis() - prevMill > 5000){
  prevMill = millis();
      sens.checkThreshold();
    int PPM =sens.getPPM();
    Serial.print("C#");
    Serial.println(PPM); 
  
  int maxOccupancy = alg.getCurMaxOccup(PPM);
  Serial.print("MAX#");
  Serial.println(maxOccupancy);
}

}
