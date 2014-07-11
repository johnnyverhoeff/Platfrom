#ifndef Motor_h
#define Motor_h

#include "MCP4921.h"

enum motor_speed {
	full_speed = 4096,
	half_speed = 2048,
	zero_speed = 0,
};

class Motor {
private:
	int _move_down_pin;
	int _move_up_pin;
	MCP4921 *speed_regulator;

public:
	Motor(int down_pin, int up_pin, int SDI, int SCK, int CS);

	void up();
	void up(motor_speed speed);
	void up(int speed);

	void down();
	void down(motor_speed speed);
	void down(int speed);

	void stop();
};

#endif