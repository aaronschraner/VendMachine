#ifndef SHIFT4_H
#define SHIFT4_H

class Shift4
{
  //notice
  //this shift register class was designed specifically for applications where
  //update speed is critical. Because of this, rather than sending data in the format
  //in[31]->SR3[7], in[30]->SR3[6]..in[0]->SR0[0]
  //it uses the format
  //in[0]->SR0[0]
  //in[1]->SR1[0]
  //in[2]->SR2[0] ... in[n]->SR{n%4}[n/4]
  //this allows direct modification of 4 bits simultaneously rather than masking each individual one.
  //  SR3  SR2  SR1  SR0     in[31]   
  //  0123 4567 89AB CDEF -> 048C 159D 26AE 37BF
  //this won't be an issue on the VFD as long as the hardware is built around this convention.
  private:
    byte clockmask, latchmask;
    byte databits; //last (LS) bit as an integer, not mask
    volatile uint8_t& ioreg;
    
  public:
    Shift4(byte clockPin, byte latchPin, byte MSdatapin);
    void load(uint32_t value);
    void update();
    inline void operator=(uint32_t value) { load(value); update(); }
    

};

#endif

