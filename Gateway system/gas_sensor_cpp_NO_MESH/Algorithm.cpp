#include "Algorithm.h"

int Algorithm::getCurMaxOccup(int PPM){
  if(PPM >= MAX_PPM)
  {
      return maxCurOccup = ((CO2_P * MAX_OCCUP * 1000000) / (PPM * AIR_INFL));
  }
  else if(PPM < MAX_PPM)
  {
      return MAX_OCCUP;
  }
}
