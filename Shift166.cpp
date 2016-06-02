#include "Shift166.h"

uint8_t Shift166::shiftIn()
{

	//load the values into the register
	port &= ~pe;
	port |= clk;
	port &= ~clk;
	port |= pe;

	byte result = 0;
	for(byte x=0x80; x; x>>=1)
	{
		port |= clk;
		port &= ~clk;
		if(pin & data)
			result |= x;
	}
	return result;
}

Shift166::Shift166(uint8_t clk, uint8_t pe, uint8_t data, volatile uint8_t& port):
	clk(clk), pe(pe), data(data), port(port), pin(*(&port - 2))
{
	*(&port - 1) = (*(&port - 1) | pe | clk) & ~data;
}
