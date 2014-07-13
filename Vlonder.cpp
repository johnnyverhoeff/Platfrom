#include "Vlonder.h"
#include "Arduino.h"

Vlonder::Vlonder() {
	// both limit switches on interrupt pins, dont know which ones yet
	_lower_limit_switch = new LimitSwitch(1);
	_upper_limit_switch = new LimitSwitch(2);

	_left_motor = new Motor(1, 2, 3, 4, 5);
	_right_motor = new Motor(1, 2, 3, 4, 5);

	_moving_state = stopped;
}

Vlonder::moving_state Vlonder::get_moving_state() {
	return _moving_state;
}

void Vlonder::up() {
	up(Motor::full_speed);
}

void Vlonder::up(Motor::speed speed) {
	up((int)speed);
}

void Vlonder::up(int speed) {
	if (!_upper_limit_switch->has_reached_limit()) return;
	_moving_state = moving_up;
	_left_motor->up(speed);
	_right_motor->up(speed);
}

void Vlonder::down() {
	down(Motor::full_speed);
}

void Vlonder::down(Motor::speed speed) {
	down((int)speed);
}

void Vlonder::down(int speed) {
	if (!_lower_limit_switch->has_reached_limit()) return;
	_moving_state = moving_down;
	_left_motor->down(speed);
	_right_motor->down(speed);
}

void Vlonder::stop() {
	_moving_state = stopped;
	_left_motor->stop();
	_right_motor->stop();
}

bool Vlonder::reached_either_limit_switch() {
	return _upper_limit_switch->has_reached_limit() || _lower_limit_switch->has_reached_limit();
}