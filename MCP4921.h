#ifndef MCP4921_h
#define MCP4921_h

class MCP4921
{
  public:
    MCP4921(int SS);
    void setValue(unsigned int Value);

  private:
    int _SLAVESELECT;
};

#endif