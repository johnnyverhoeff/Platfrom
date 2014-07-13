#ifndef Motor_h
#define Motor_h

#include "MCP4921.h"

//moet kijken naar de spi lib van arduino gebruiken

class Motor {
private:
	int _move_down_pin;
	int _move_up_pin;
	MCP4921 *speed_regulator;

public:
	Motor(int down_pin, int up_pin, int SDI, int SCK, int CS);

	enum speed {
		full_speed = 4096,
		half_speed = 2048,
		zero_speed = 0,
	};

	virtual void up();
	virtual void up(speed speed);
	virtual void up(int speed);

	virtual void down();
	virtual void down(speed speed);
	virtual void down(int speed);

	virtual void stop();

	
};

#endif