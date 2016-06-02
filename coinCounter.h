#ifndef COINCOUNTER_H
#define COINCOUNTER_H
const int QUARTER_PIN = 18;
const int DIME_PIN = 20;
const int NICKEL_PIN = 19;
struct CoinCounts
{
  volatile int
    quarters,
    dimes,
    nickels;
  volatile unsigned long blockoutMillis;
  int getMoney() { return quarters * 25 + dimes * 10 + nickels * 5; }
  void init();
} COIN_COUNTS;
enum CoinType
{
  _QUARTER,
  _NICKEL,
  _DIME
};
void QuarterInserted()
{
  if(millis() - COIN_COUNTS.blockoutMillis > 100) 
    COIN_COUNTS.quarters++; 
  COIN_COUNTS.blockoutMillis = millis();
}
  
void DimeInserted()
{
  if(millis() - COIN_COUNTS.blockoutMillis > 100) 
    COIN_COUNTS.dimes++; 
  COIN_COUNTS.blockoutMillis = millis();
}

void NickelInserted()
{
  if(millis() - COIN_COUNTS.blockoutMillis > 100) 
    COIN_COUNTS.nickels++; 
  COIN_COUNTS.blockoutMillis = millis();
}

#endif
