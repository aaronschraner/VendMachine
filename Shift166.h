#ifndef SHIFT166_H
#define SHIFT166_H
#include "Arduino.h"
class Shift166
{
	private:
		uint8_t clk, pe, data; //masks for various pins
		volatile uint8_t &port, &pin;
	public:
		Shift166(uint8_t clk, uint8_t pe, uint8_t data, volatile uint8_t& port);
		uint8_t shiftIn();
};

#endif

