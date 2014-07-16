#include "Vlonder.h"
#include "Arduino.h"

Vlonder::Vlonder() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("Vlonder::Vlonder called");
	#endif
	// both limit switches on interrupt pins, dont know which ones yet
	_lower_limit_switch = new LimitSwitch(1);
	_upper_limit_switch = new LimitSwitch(2);

	_left_motor = new Motor(1, 2, 3, 4, 5);
	_right_motor = new Motor(1, 2, 3, 4, 5);

	_moving_state = stopped;
}

Vlonder::moving_state Vlonder::get_moving_state() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("Vlonder::get_moving_state called with outcome: ");
		Serial.println(_moving_state);
	#endif

	return _moving_state;
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

	if (!_upper_limit_switch->has_reached_limit()) return;
	_moving_state = moving_up;
	_left_motor->up(speed);
	_right_motor->up(speed);
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

	if (!_lower_limit_switch->has_reached_limit()) return;
	_moving_state = moving_down;
	_left_motor->down(speed);
	_right_motor->down(speed);
}

void Vlonder::stop() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("Vlonder::stop called");
	#endif

	_moving_state = stopped;
	_left_motor->stop();
	_right_motor->stop();
}