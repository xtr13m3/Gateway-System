#ifndef ALGORITHM_H
#define ALGORITHM_H

#define CO2_P 0.02088 //  CO2 amount in kg/m3 per hour per person
#define AIR_INFL 32 // Air inflow in kg/m3 per hour per person
#define MAX_PPM 800 // Max PPM threshold 
#define MAX_OCCUP 1000

class Algorithm{
  private:
    int co2, airInfl, maxPpm, maxOccup;
    int maxCurOccup;

  public:
    Algorithm(int co2,int airInfl,int maxPpm,int maxOccup){
      this->co2 = co2;
      this->airInfl = airInfl;
      this->maxPpm = maxPpm;
      this->maxOccup = maxOccup;
    }
    
    int getCurMaxOccup(int PPM);
};

#endif
