#ifndef HELPBTN_H
#define HELPBTN_H

#define BTN 39

class Button{
  private:
  int pin;
  unsigned long prevMill;

  public:
    Button(int pin){
      this->pin = pin;

      pinMode(pin, INPUT_PULLUP);
    }
  int btnPressed(void);
};

#endif
