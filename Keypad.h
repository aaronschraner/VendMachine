#ifndef KEYPAD_H
#define KEYPAD_H

class Keypad
{
  private:
    const byte rows, cols;
    byte* rowPins;
    byte* colPins;
    const char* symbols;

  public:
    Keypad(byte rows, byte cols, byte* rowPins, byte* colPins, const char* symbols);
    inline char getSymbol(byte row, byte col) { return symbols[row*cols + col]; }
    char scan();
    void print();
  
    
  
};

#endif

