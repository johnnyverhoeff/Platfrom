#ifndef Vlonder_h
#define Vlonder_h

#include "LimitSwitch.h"
#include "Motor.h"
#include "WaterSensor.h"
#include "Vlonder_enums.h"

class Vlonder {

public:
	Vlonder();

	vlonder_moving_states get_moving_state();

	WaterSensor *active_water_sensor;

	bool reach_active_water_sensor();
	
	void up();
	void up(Motor::speed speed);
	void up(int speed);

	void down();
	void down(Motor::speed speed);
	void down(int speed);
	
	void stop();

private:
	vlonder_moving_states _moving_state;

	LimitSwitch *_upper_limit_switch;
	LimitSwitch *_lower_limit_switch;
	bool reached_either_limit_switch();

	Motor *_left_motor;
	Motor *_right_motor;
};

#endif