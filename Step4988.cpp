#include "Step4988.h"

void Step4988::rotate(int16_t deg)
{
  enable();
  digitalWrite(dirPin, deg < 0);
  for(int16_t i=0; i<abs(deg*5/9); i++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delay(5);
  }
}
void Step4988::microtate(float deg)
{
  enable();
  digitalWrite(dirPin, deg < 0);
  for(int16_t i=0; i<abs(deg*5/9) * 16; i++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(140);
  }
}
void Step4988::enable()
{
  digitalWrite(enablePin, 0);
}

void Step4988::disable()
{
  digitalWrite(enablePin, 1);
}

Step4988::Step4988(byte stepPin, byte dirPin, byte enablePin):
  stepPin(stepPin), dirPin(dirPin), enablePin(enablePin)
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
}
