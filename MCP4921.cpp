#include "Arduino.h"
#include "MCP4921.h"

MCP4921::MCP4921(int SDI, int SCK, int CS)
{
	_DATAOUT = SDI;
	_SPICLOCK = SCK;
	_SLAVESELECT = CS;

	pinMode(_DATAOUT, OUTPUT);
	pinMode(_SPICLOCK, OUTPUT);
	pinMode(_SLAVESELECT, OUTPUT);
}

void MCP4921::setValue(int Value) {
	sendIntValueSPI(Value);
}

void MCP4921::sendSPIClock() {
	digitalWrite(_SPICLOCK, HIGH);
	digitalWrite(_SPICLOCK, LOW);
	delay(1);
}

void MCP4921::sendSPIHeader() {
	// bit 15
	// 0 write to DAC *
	// 1 ignore command
	digitalWrite(_DATAOUT, LOW);
	sendSPIClock();
	// bit 14 Vref input buffer control
	// 0 unbuffered *
	// 1 buffered
	digitalWrite(_DATAOUT, LOW);
	sendSPIClock();
	// bit 13 Output Gain selection
	// 0 2x
	// 1 1x *
	digitalWrite(_DATAOUT, HIGH);
	sendSPIClock();
	// bit 12 Output shutdown control bit
	// 0 Shutdown the device
	// 1 Active mode operation *
	digitalWrite(_DATAOUT, HIGH);
	sendSPIClock();
}

void MCP4921::sendIntValueSPI(int value) {
	// initiate data transfer with 4921
	digitalWrite(_SLAVESELECT, LOW);

	// send 4 bit header
	sendSPIHeader();

	// send data
	for (int i = 11; i >= 0; i--){
		digitalWrite(_DATAOUT, ((value&(1 << i))) >> i);
		sendSPIClock();
	}

	// finish data transfer
	digitalWrite(_SLAVESELECT, HIGH);
}