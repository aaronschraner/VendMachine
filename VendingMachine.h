#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H
#include "tinyVFD.h"
#include "Step4988.h"
#include "Keypad.h"
#include <Servo.h>
Servo sodaServo;
const int servoPin = 4;
//
//struct VMPins
//{
//  byte
//    *stepperStepPins, //[5]
//    stepperDirPin,
//    microStepPins,
//    *servoPins; //[4]
//  VMPins(byte *stepperStepPins, byte stepperDirPin, byte microStepPin, byte *servoPins):
//    stepperStepPins(stepperStepPins), stepperDirPin(stepperDirPin), microStepPin(microStepPin),
//    servoPins(servoPins)
//  {
//  }
//};
enum VMState
{
  _INSULT,
  _COLLECT,
  _SELECT,
  _VENDING
};
class VendingMachine
{
  private:
    TinyVFD& vfd;
    Keypad& keypad;
    Step4988** steppers;
    Servo* servos;
    int machineMoney, userMoney;
  public:
    VendingMachine(TinyVFD& vfd, Keypad& keypad, Step4988** steppers, Servo* servos):
      state(_INSULT), vfd(vfd), keypad(keypad), steppers(steppers), servos(servos)
    {
      sodaServo.attach(servoPin);
      sodaServo.write(250);
    }
    VMState state;
    void operate();
    void insultUser();
    void enteringChange();
    byte selectItem();
    char getSelection();
    void dispenseChange();
    void vendItem(byte index);
    byte toIndex(char row, byte col);
    
  
    
};
#endif

