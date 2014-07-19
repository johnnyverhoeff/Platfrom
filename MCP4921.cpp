#include "MCP4921.h"
#include "SPI\SPI.h"

MCP4921::MCP4921(int SS)
{
	_SLAVESELECT = SS;
	pinMode(_SLAVESELECT, OUTPUT);
}

void MCP4921::setValue(unsigned int Value) {
	digitalWrite(_SLAVESELECT, LOW);

	word data = highByte(Value);

	data &= 15;// 0b00001111;
	data |= 48;// 0b00110000;

	SPI.transfer(data);

	data = lowByte(Value);

	SPI.transfer(data);

	digitalWrite(_SLAVESELECT, HIGH);
}