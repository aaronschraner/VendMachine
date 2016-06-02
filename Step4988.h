#ifndef STEP4988_H
#define STEP4988_H
#include "Arduino.h"
class Step4988
{
  private:
    byte stepPin, dirPin, enablePin;
  public:
    Step4988(byte stepPin, byte dirPin, byte enablePin);
    void rotate(int16_t deg);
    void microtate(float deg);
    void disable();
    void enable();
    
};

#endif
