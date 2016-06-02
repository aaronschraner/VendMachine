#include "VendingMachine.h"
void VendingMachine::operate()
{
  static byte x;
  switch(state)
  {
    case _INSULT: insultUser(); break;
    case _COLLECT: enteringChange(); break;
    case _SELECT: vendItem(selectItem()); break;
    case _VENDING: break;
  }
}
void VendingMachine::insultUser()
{
  Serial.println("Insulting user...");
  machineMoney = COIN_COUNTS.getMoney();
  for(byte i=0; i<12; i++)
    vfd.setChar(i, "WELCOME     "[i]);
  while(COIN_COUNTS.getMoney() == machineMoney);
  state = _COLLECT;
}

void VendingMachine::enteringChange()
{
  Serial.println("Waiting for change....");
  //vfd.setExtra(TinyVFD::_COLON, 1);
  for(int i=0; i<8; i++)
    vfd.setChar(i, "CREDIT  "[i]);
  while(!keypad.scan())
  {
    userMoney = COIN_COUNTS.getMoney() - machineMoney;
    vfd.setChar(8,  '0' + (userMoney / 1000) % 10);
    vfd.setChar(9,  '0' + (userMoney / 100) % 10);
    vfd.setChar(10, '0' + (userMoney / 10) % 10);
    vfd.setChar(11, '0' + (userMoney / 1) % 10);
  
  }
  state = _SELECT;
  //vfd.setExtra(TinyVFD::_COLON, 0);
  return;
  
}

byte VendingMachine::selectItem()
{
  for(int i=0; i<6; i++)
    vfd.setChar(i, ' ');
  vfd.setChar(7, '_');
  char row = getSelection();
  vfd.setChar(6, row);
  while(keypad.scan());
  char col = getSelection();
  vfd.setChar(7, col);
  while(keypad.scan());
  state = _VENDING;
  return toIndex(row, col - '0');
}

char VendingMachine::getSelection()
{
  char res;
  while(!(res = keypad.scan()));
  return res;
    
}

byte VendingMachine::toIndex(char row, byte col)
{
  vfd.setChar(10, row);
  vfd.setChar(11, col + '0');
  vfd.setChar(9, ' ');
  vfd.setChar(8, ' ');
  switch(row)
  {
    case 'A': return col - 1;
    case 'B': return col + 1;
    case 'C': return col + 4;
    default: return 8;
  }
}

void VendingMachine::vendItem(byte index)
{
  
  for(int i=0; i<8; i++)
    vfd.setChar(i, "VENDING "[i]);
  Serial.print("Vending item ");
  Serial.print((int)index);
  Serial.println("....");
  switch(index)
  {
    case 0: steppers[0] -> rotate(360); break;
    case 1: steppers[1] -> rotate(360); break;
    case 2: steppers[2] -> rotate(360); break;
    case 3: steppers[3] -> rotate(360); break;
    case 4: steppers[4] -> rotate(360); break;
    case 5: sodaServo.attach(servoPin); sodaServo.write(128); delay(1000); sodaServo.write(250); delay(1000);sodaServo.detach(); break;
    default: {
      for(int i=0; i<8; i++)
        vfd.setChar(i, "INVALID "[i]);
      delay(2000);
    } break;
  }
  state = _INSULT;
}

