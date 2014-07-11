#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int down_pin, int up_pin) {
	_move_down_pin = down_pin;
	_move_up_pin = up_pin;

	pinMode(_move_up_pin, OUTPUT);
	pinMode(_move_down_pin, OUTPUT);

	digitalWrite(_move_up_pin, LOW);
	digitalWrite(_move_down_pin, LOW);
}

void Motor::down() {
	digitalWrite(_move_down_pin, HIGH);
	// other stuff with spi 
}

void Motor::up() {
	digitalWrite(_move_up_pin, HIGH);
	// other stuff with spi 
}

void Motor::stop() {
	digitalWrite(_move_down_pin, LOW);
	digitalWrite(_move_up_pin, LOW);
	// other stuff with spi 
}