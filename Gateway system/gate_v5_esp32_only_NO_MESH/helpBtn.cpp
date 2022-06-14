#ifndef HELPBTN_CPP
#define HELPBTN_CPP

#include "Arduino.h" 
#include "helpBtn.h"

int Button::btnPressed(void)
{
  int btnState = digitalRead(pin);
  
  if(millis() - prevMill > 200)
  {
    prevMill = millis();

    if(btnState == HIGH)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}

#endif
