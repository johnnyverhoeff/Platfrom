#ifndef Motor_h
#define Motor_h

#include "MCP4921.h"

//moet kijken naar de spi lib van arduino gebruiken

class Motor {
public:
	enum speed {
		full_speed = 4096,
		half_speed = 2048,
		zero_speed = 0,
	};

	enum movement {
		move_up,
		move_down,
	};

private:
	int _move_down_pin;
	int _move_up_pin;
	MCP4921 *speed_regulator;

	void move(movement movement, int speed);

public:
	Motor(int down_pin, int up_pin, int SDI, int SCK, int CS);

	virtual void up();
	virtual void up(speed speed);
	virtual void up(int speed);

	virtual void down();
	virtual void down(speed speed);
	virtual void down(int speed);

	virtual void stop();

	
};

#endif