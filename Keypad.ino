#include "Keypad.h"

Keypad::Keypad(byte rows, byte cols, byte* rowPins, byte* colPins, const char* symbols):
  rows(rows), cols(cols)
{
  //sweep by columns, read rows
  this->rowPins = rowPins; //new byte[rows];
  this->colPins = colPins; //new byte[cols];
  this->symbols = symbols; // new char[rows * cols];
  for (byte r = 0; r < rows; r++)
  {
    this->rowPins[r] = rowPins[r];
    pinMode(rowPins[r], INPUT_PULLUP);
    for (byte c = 0; c < cols; c++)
    {
      if (r == 0)
      {
        this->colPins[c] = colPins[c];
        pinMode(colPins[c], INPUT_PULLUP);
      }
//      this->symbols[r * cols + c] = symbols[r * cols + c];
    }
  }

}

char Keypad::scan()
{
  char sym=0x00;
  for(byte c=0; c<cols; c++) pinMode(colPins[c], INPUT_PULLUP);
  for(byte r=0; r<cols; r++) pinMode(rowPins[r], INPUT_PULLUP);
  for (byte c = 0; c < cols; c++)
  {
    pinMode(colPins[c], OUTPUT);
    digitalWrite(colPins[c], LOW);
    for (byte r = 0; r < rows; r++)
    {
      if(!digitalRead(rowPins[r]))
      {
        sym = getSymbol(r, c); // "123456789*0#"[r*cols+c];
        return sym;
      }

    }
    pinMode(colPins[c], INPUT_PULLUP);
    
  }
  return sym;
}

void Keypad::print()
{
  Serial.println("rows:");
  for(byte r=0; r<rows; r++)
    Serial.println(rowPins[r]);
  Serial.println("cols:");
  for(byte c=0; c<cols; c++)
    Serial.println(colPins[c]);
    
}

