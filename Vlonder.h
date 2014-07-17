#ifndef Vlonder_h
#define Vlonder_h

#include "LimitSwitch.h"
#include "Motor.h"
#include "WaterSensor.h"
#include "WaterMeasurer.h"
#include "Vlonder_enums.h"

class Vlonder {

public:
	Vlonder();

	vlonder_moving_states get_moving_state();

	void set_active_water_sensor(WaterSensor *sensor);
	WaterMeasurer water_measurer;

	bool reach_active_water_sensor();
	void control_at_active_water_sensor();
	
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

	Motor *_left_motor;
	Motor *_right_motor;

	WaterSensor *active_water_sensor;


};

#endif