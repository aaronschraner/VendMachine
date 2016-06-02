#ifndef TINYVFD_H
#define TINYVFD_H
#include "Shift4.h"
#include "chardefs.h"

#define VFD_REFRESH_DEL 500 //us

class TinyVFD
{
  private:
    uint16_t data[10];
    Shift4 interface;
    uint8_t extrabits;

  public:
    TinyVFD(byte clock, byte latch, byte d0);
    void init();
    static TinyVFD* single;
    void render();
    inline void render(byte dig);
    void setraw(byte index, uint16_t value) {
      data[index] = value;
    }
    uint16_t& operator[](byte i) {
      return data[i];
    }
    void setChar(byte index, char c)
    {
      if (index < 8)
        data[index] = charTo14seg(c);
      else if (index % 2)
        data[index / 2 + 4] = (data[index / 2 + 4] & ~0x3F20) |
                              sevsegTo14seg(charTo7seg(c), 1);
      else
        data[index / 2 + 4] = (data[index / 2 + 4] & 0x3F20) |
                              sevsegTo14seg(charTo7seg(c), 0);

    }
    void setExtraBits(uint8_t value)
    {
      extrabits = value;
    }
    enum Extra //first (most sig.) 4 bits are mask for segment, least sig. 4 bits are which data[] it's in
    {
      _POWER    = 0x20,
      _FANBL    = 0x81,
      _FANN     = 0x21,
      _FANBAR   = 0x41,
      _AM       = 0x22,
      _PM       = 0x82,
      _HAND     = 0x42,
      _OZ       = 0x27,
      _KG       = 0x87,
      _LBS      = 0x47,
      _COLON    = 0x88,
      _PERIOD   = 0x48
    };
    void setExtra(Extra e, bool value)
    {
      data[e & 0xF] = value ? data[e & 0xF] | (e & 0xF0) : data[e & 0xF] & ~(e & 0xF0);
    }

};
TinyVFD* TinyVFD::single;

void VFDrenderer()
{
  static byte scancolumn;
  TinyVFD::single->render(scancolumn);
  scancolumn = (scancolumn + 1 ) % 10;
}


#endif

