#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int down_pin, int up_pin, int SDI, int SCK, int CS) {
	_move_down_pin = down_pin;
	_move_up_pin = up_pin;

	pinMode(_move_up_pin, OUTPUT);
	pinMode(_move_down_pin, OUTPUT);

	digitalWrite(_move_up_pin, LOW);
	digitalWrite(_move_down_pin, LOW);

	speed_regulator = new MCP4921(SDI, SCK, CS);
	speed_regulator->setValue(zero_speed);
}

void Motor::move(movement movement, int speed) {
	switch (movement) {
		case move_up:
			digitalWrite(_move_up_pin, HIGH);
			digitalWrite(_move_down_pin, LOW);
			break;
		case move_down:
			digitalWrite(_move_up_pin, LOW);
			digitalWrite(_move_down_pin, HIGH);
			break;
		case stop_moving: default:
			digitalWrite(_move_up_pin, LOW);
			digitalWrite(_move_down_pin, LOW);	
	}

	speed_regulator->setValue(speed);
}

void Motor::down() {
	down(full_speed);
}

void Motor::down(speed speed) {
	down((int)speed);
}

void Motor::down(int speed) {
	move(move_down, speed);
}

void Motor::up() {
	up(full_speed);
}

void Motor::up(speed speed) {
	up((int)speed);
}

void Motor::up(int speed) {
	move(move_up, speed);
}

void Motor::stop() {
	move(stop_moving, zero_speed);
}