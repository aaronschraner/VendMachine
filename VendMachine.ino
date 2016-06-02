#include "tinyVFD.h"
#include "Keypad.h"
#include "coinCounter.h"
#include "VendingMachine.h"
#define MEGA

#ifdef UNO
const clk = 2, lat = 3, dLSB = 4;
#elif defined(MEGA)
const byte vfdclk = A0, vfdlat = A1, vfdLSB = A2,
  keypadclk=A8, keypadpe=A9, keypaddata=A10;
#elif defined(TINY)
const byte clk = 0, lat = 1, dLSB = 9;
#endif




void setup()
{
  
}

#if defined(MEGA) || defined(UNO)
void loop()
{
  Serial.begin(9600);
  //Shift4 shift4(clk, lat, dLSB);
  Servo servos[4];
  TinyVFD vfd(vfdclk, vfdlat, vfdLSB);
  byte rowPins [] = {52, 50, 38, 40};
  byte colPins [] = {48, 46, 44, 42};
  Keypad keypad(4, 4, rowPins, colPins, "123A456B789C*0#.");
  vfd.init();
  COIN_COUNTS.init();
  int stepPins[5] = {12, 11, 10, 9, 8};
  Step4988** steppers = new Step4988* [5];
  for(int i=0; i < 5; i++)
    steppers[i] = new Step4988(stepPins[i], 7, 6);
  
  VendingMachine machine(vfd, keypad, steppers, servos);
  for(int i=0; i<12; i++)
    vfd.setChar(i, "VENDTRON2016"[i]);
  delay(1000);
  sodaServo.detach();
  while (true)
  {
    machine.operate();
  }
}

#endif



