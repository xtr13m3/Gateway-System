#ifndef CO2SENSOR_CPP
#define CO2SENSOR_CPP

#include "co2Sensor.h"

float CO2Sensor::getResistance(void) {
  int val = analogRead(mqPin);
  return ((1023./(float)val) * 5. - 1.)*RLOAD;
}

float CO2Sensor::getPPM(void) {
    return PARA * pow((getResistance()/RZERO), -PARB);
}

/*
 * Uncomment following to calibrate sensor in new compartment 
 */

//float CO2Sensor::getRZero() {
//  return getResistance() * pow((ATMOCO2/PARA), (1./PARB));
//}


void CO2Sensor::checkThreshold(void){
    if(millis() - sensMillis > INTERVAL_SENS){
        sensMillis = millis();
        float ppm = getPPM();
        if(ppm > PPM_THRESHOLD){
          digitalWrite(led, HIGH);
        }
        else
        {
          digitalWrite(led, LOW);
        }
    }
}
#endif
