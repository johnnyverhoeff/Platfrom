#include "Vlonder.h"
#include "Arduino.h"

Vlonder::Vlonder() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("Vlonder::Vlonder called");
	#endif
	// both limit switches on interrupt pins, dont know which ones yet
	_lower_limit_switch = new LimitSwitch(30);
	_upper_limit_switch = new LimitSwitch(31);

	_left_motor = new Motor(40, 41, 42);
	_right_motor = new Motor(43, 44, 45);
	
	_moving_state = vlonder_stopped;
}

vlonder_moving_states Vlonder::get_moving_state() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("Vlonder::get_moving_state called with outcome: ");
		Serial.println(_moving_state);
	#endif

	return _moving_state;
}

bool Vlonder::reach_active_water_sensor() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("Vlonder::reach_active_water_sensor called with active sensor: ");
		Serial.println(active_water_sensor->get_name());
	#endif

	if (!active_water_sensor->has_reached_position(_moving_state))
	{
		if (active_water_sensor->must_move_up_to_reach_position())
			up();
		else
			down();

		return false;
	}
	else
	{
		stop();
		return true;
	}
		
}

void Vlonder::set_active_water_sensor(WaterSensor *sensor) {
	active_water_sensor = sensor;
	water_measurer.active_water_sensor = sensor;
}

void Vlonder::control_at_active_water_sensor() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("Vlonder::control_at_active_water_sensor called with active sensor: ");
		Serial.println(active_water_sensor->get_name());
	#endif

	switch (_moving_state) {
		case vlonder_moving_up:
			up_with_time(water_measurer.get_motor_on_time());
			return;

		case vlonder_moving_down:
			down_with_time(water_measurer.get_motor_on_time());
			return;

		case vlonder_stopped:
		default:
			break;
	}

	switch (water_measurer.get_measure_results()) {
		case WaterMeasurer::move_up:
			up_with_time(water_measurer.get_motor_on_time());
			break;

		case WaterMeasurer::move_down:
			down_with_time(water_measurer.get_measure_results());
			break;

		case WaterMeasurer::stay_at_position: 
		case WaterMeasurer::undetermined: 
		default:
			break;

	}
}


void Vlonder::up() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("Vlonder::up called");
	#endif

	up(Motor::full_speed);
}

void Vlonder::up(Motor::speed speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("Vlonder::up called with param: ");
		Serial.println(speed);
	#endif

	up((int)speed);
}

void Vlonder::up(int speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("Vlonder::up called with param: ");
		Serial.println(speed);
	#endif

	if (_upper_limit_switch->has_reached_limit()) {
		stop();
		return;
	}
	_moving_state = vlonder_moving_up;
	_left_motor->up(speed);
	_right_motor->up(speed);
}

void Vlonder::up_with_time(int on_time) {
	up_with_time(on_time, Motor::full_speed);
}

void Vlonder::up_with_time(int on_time, Motor::speed speed) {
	up_with_time(on_time, (int)speed);
}

void Vlonder::up_with_time(int on_time, int speed) {
	if (_upper_limit_switch->has_reached_limit()) {
		stop();
		return;
	}

	_moving_state = vlonder_moving_up;

	if (!_left_motor->up_with_time(on_time, speed) &
		!_right_motor->up_with_time(on_time, speed))
		stop();
}

void Vlonder::down() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("Vlonder::down called");
	#endif

	down(Motor::full_speed);
}

void Vlonder::down(Motor::speed speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("Vlonder::down called with param: ");
		Serial.println(speed);
	#endif

	down((int)speed);
}

void Vlonder::down(int speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("Vlonder::down called with param: ");
		Serial.println(speed);
	#endif

	if (_lower_limit_switch->has_reached_limit()) {
		stop();
		return;
	}
	_moving_state = vlonder_moving_down;
	_left_motor->down(speed);
	_right_motor->down(speed);
}

void Vlonder::down_with_time(int on_time) {
	down_with_time(on_time, Motor::full_speed);
}

void Vlonder::down_with_time(int on_time, Motor::speed speed) {
	down_with_time(on_time, (int)speed);
}

void Vlonder::down_with_time(int on_time, int speed) {
	if (_lower_limit_switch->has_reached_limit()) {
		stop();
		return;
	}

	_moving_state = vlonder_moving_down;

	if (!_left_motor->down_with_time(on_time, speed) &
		!_right_motor->down_with_time(on_time, speed))
		stop();
}

void Vlonder::stop() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("Vlonder::stop called");
	#endif

	_moving_state = vlonder_stopped;
	_left_motor->stop();
	_right_motor->stop();
}