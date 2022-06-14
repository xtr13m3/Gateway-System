#include "gateServo.h"
#include "gateDetector.h"
#include "helpBtn.h"

Gate gate = Gate(PWM_FREQ, PWM_CH,PWM_RES, SERVO);
MovDetector D1 = MovDetector(TRIG_1, ECHO_1, LED_1);
MovDetector D2 = MovDetector(TRIG_2, ECHO_2, LED_2);
Button btn = Button(BTN);

int dist1, dist2, occCounter;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  dist1 = D1.measureDist();
  dist2 = D2.measureDist();
  
  occupCounter(dist1, dist2);
//  Serial.println(occCounter);
  int pressed = btn.btnPressed();
  if(pressed == 1)
  {
    Serial.print("G1#");
    Serial.println("HELP");
  }
}

void occupCounter(int dist1, int dist2){
  if((dist1 > 0 && dist1 <= 10) && !(dist2 > 0 && dist2 <=10))
  {
    occCounter++;
    Serial.print("G1#");
    Serial.println(occCounter);
    digitalWrite(LED_1, HIGH);
    gate.openGate();
    delay(5000);

  }
  else if(!(dist1 > 0 && dist1 <= 10) && (dist2 > 0 && dist2 <= 10)){
    occCounter--;
    Serial.print("G1#");
    Serial.println(occCounter);
    digitalWrite(LED_2, HIGH);
    gate.openGate();
    delay(5000);
  }
  else
  {
    gate.closeGate();
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
  }
}
