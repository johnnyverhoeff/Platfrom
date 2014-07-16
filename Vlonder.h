#ifndef Vlonder_h
#define Vlonder_h

#include "LimitSwitch.h"
#include "Motor.h"

class Vlonder {

public:
	enum moving_state {
		moving_up,
		moving_down,
		stopped,
	};

	Vlonder();

	moving_state get_moving_state();
	
	void up();
	void up(Motor::speed speed);
	void up(int speed);

	void down();
	void down(Motor::speed speed);
	void down(int speed);
	
	void stop();

private:
	moving_state _moving_state;

	LimitSwitch *_upper_limit_switch;
	LimitSwitch *_lower_limit_switch;
	bool reached_either_limit_switch();

	Motor *_left_motor;
	Motor *_right_motor;
};

#endif