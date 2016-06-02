#include "coinCounter.h"

void CoinCounts::init()
{
  pinMode(QUARTER_PIN, INPUT);
  pinMode(DIME_PIN, INPUT);
  pinMode(NICKEL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(QUARTER_PIN), QuarterInserted, RISING);
  attachInterrupt(digitalPinToInterrupt(DIME_PIN),    DimeInserted,    RISING);
  attachInterrupt(digitalPinToInterrupt(NICKEL_PIN),  NickelInserted,  RISING);
  
}

