#include "tinyVFD.h"
#include "TimerOne.h"

TinyVFD::TinyVFD(byte clock, byte latch, byte d0):
  interface(clock, latch, d0),
  data{0}, extrabits(0)
{
  single = this;
}
void TinyVFD::init()
{
  noInterrupts();
  Timer1.initialize(VFD_REFRESH_DEL);
  Timer1.attachInterrupt(VFDrenderer);
  interrupts();
}
void TinyVFD::render(byte index)
{
  interface.load((~(0x00010000 << index | data[index]) & 0x03FFFFFF) | (uint32_t)(extrabits&0xFC) << 24);
  interface.update();
}

void TinyVFD::render()
{
  for(byte i=0; i<10; i++)
  {
    render(i);
    delay(1);
  }
}

