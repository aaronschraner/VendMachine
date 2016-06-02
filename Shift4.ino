#include "Shift4.h"

Shift4::Shift4(byte clockPin, byte latchPin, byte MSdatapin):
  ioreg(*portOutputRegister(digitalPinToPort(MSdatapin)))
{
  clockmask = digitalPinToBitMask(clockPin);
  latchmask = digitalPinToBitMask(latchPin);
  byte mask = digitalPinToBitMask(MSdatapin);
  for(databits=0; (0x01<<databits) & ~mask; databits++);
  *portModeRegister(digitalPinToPort(MSdatapin)) |= (0x0F << databits) | latchmask | clockmask; //set pins as outputs
  
}

void Shift4::load(uint32_t value)
{
  byte datamask = 0x0F << databits;
  byte allmask = datamask | clockmask;
  byte basereg = ioreg & ~allmask;
  for(byte x=0; x < 8; x++)
  {
    ioreg = basereg | ((value >> (7 - x) * 4) << databits ) & datamask;
    ioreg |= clockmask;
    
  }
  ioreg = basereg;
}

void Shift4::update()
{
  ioreg &= ~latchmask;
  ioreg |= latchmask;
  
}

