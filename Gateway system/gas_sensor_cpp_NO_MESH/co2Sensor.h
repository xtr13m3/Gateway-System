#ifndef CO2SENSOR_H
#define CO2SENSOR_H

#include "Arduino.h"

/// The load resistance on the board
#define RLOAD 10.0

/// Calibration resistance at atmospheric CO2 level
#define RZERO 105

/// Parameters for calculating ppm of CO2 from sensor resistance
#define PARA 116.6020682
#define PARB 2.769034857

/// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

/// Atmospheric CO2 level for calibration purposes
#define ATMOCO2 397.13

/// Pin declaration and threshold setting 
#define MQ_PIN 39
#define LED 4
#define INTERVAL_SENS 5000
#define PPM_THRESHOLD 400

class CO2Sensor
{
  private:
    int mqPin, led;
    unsigned long sensMillis;

  public:
    CO2Sensor(int mqPin, int led){
      this->mqPin = mqPin;
      this->led = led;
  
      pinMode(mqPin, INPUT);
      pinMode(led, OUTPUT);
    }

/*
 * Uncomment to find RZero in a new facility 
 * for correct CO2 measurement. After finding
 * value, change RZero value in MQ135.h or define 
 * constant on the top of this file in defines
 */

  float getResistance(void);
  float getPPM(void);
//  float getRZero();

  void checkThreshold(void);   
};

#endif
