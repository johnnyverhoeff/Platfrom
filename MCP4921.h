#ifndef MCP4921_h
#define MCP4921_h

#include "Arduino.h"

//moet kijken naar de spi lib van arduino gebruiken

class MCP4921
{
  public:
    MCP4921(int SDI, int SCK,int CS);
    void setValue(int Value);

  private:
    int _DATAOUT;
    int _SPICLOCK;
    int _SLAVESELECT;

    void sendSPIHeader();
    void sendIntValueSPI(int value);
    void sendSPIClock();
};

#endif