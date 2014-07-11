#include "LimitSwitch.h"
#include "Arduino.h"

LimitSwitch::LimitSwitch(int pin) : _pin(pin) {
	pinMode(_pin, INPUT);
}

bool LimitSwitch::has_reached_limit() {
	// maybe negative depending on pos or neg logic
	return digitalRead(_pin);
}