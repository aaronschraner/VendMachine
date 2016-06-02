#include "chardefs.h"



uint16_t sevsegTo14seg(uint8_t sevseg, uint8_t digit)
{
  uint16_t temp=sevseg;
  return digit ?
    (((temp << 7)&0x3F00) | ((temp&0x01)<<6)):
    ((temp << 14) | (temp >> 2));
}

uint8_t charTo7seg(char c)
{
  if(c >= '0' && c <= '9')
    return SEVSEG_NUMS[c-'0'];
  if(c >= 'A' && c <= 'F')
    return SEVSEG_NUMS[c-'A'+10];
  switch(c)
  {
    case ' ': return 0;
    default: return 0b0001000;
  }
    
}

uint16_t charTo14seg(char input)
{

  if (input <= 'Z' && input >= 'A')
    return lcLetters[input - 'A'];
  else if (input >= '0' && input <= '9')
    return anums[input - '0'];
  else if (input >= 'a' && input <= 'z')
    return lcLetters[32 + input - 'a'];
  else //specific cases
  {
    switch (input)
    {
      case '_': return 0x8000 >> 7;
      case '-': return 0x4000;
      case ' ': return 0;
      case '#': return 0b1111101000001011;
      case '.': return 0x8000 >> 6;
    }
  }
  return 0b0100111000001110;
}

