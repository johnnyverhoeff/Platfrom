#include "MotorWithBrake.h"
#include "Arduino.h"

MotorWithBrake::MotorWithBrake(int down_pin, int up_pin, int brake_pin, int SDI, int SCK, int CS) :
	Motor(down_pin, up_pin, SDI, SCK, CS) {
	_brake_pin = brake_pin;
	pinMode(_brake_pin, OUTPUT);
	_attach_brake();
}

void MotorWithBrake::_attach_brake() {
	digitalWrite(_brake_pin, LOW);
	//maybe inverse due to neg or pos logic
}

void MotorWithBrake::_release_brake() {
	digitalWrite(_brake_pin, HIGH);
	//maybe inverse due to neg or pos logic
}

void MotorWithBrake::up() {
	Motor::up(half_speed);
	_release_brake();
	Motor::up();
}
void MotorWithBrake::up(speed speed) {
	Motor::up(half_speed);
	_release_brake();
	Motor::up(speed);
}

void MotorWithBrake::up(int speed) {
	Motor::up(half_speed);
	_release_brake();
	Motor::up(speed);
}

void MotorWithBrake::down() {
	Motor::down(half_speed);
	_release_brake();
	Motor::down();
}

void MotorWithBrake::down(speed speed) {
	Motor::down(half_speed);
	_release_brake();
	Motor::down(speed);
}

void MotorWithBrake::down(int speed) {
	Motor::down(half_speed);
	_release_brake();
	Motor::down(speed);
}

void MotorWithBrake::stop() {
	Motor::stop();
	_attach_brake();
}