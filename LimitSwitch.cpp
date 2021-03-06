#include "LimitSwitch.h"
#include "Arduino.h"

LimitSwitch::LimitSwitch(int pin, const char *name) : _pin(pin), _name(name) {
	pinMode(_pin, INPUT);
	
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"LimitSwitch\" Constructor called with pin: ");
		Serial.println(_pin);
	#endif
}

bool LimitSwitch::has_reached_limit() {
	// maybe negative depending on pos or neg logic
	bool result =  digitalRead(_pin);
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"LimitSwitch::has_reached_limit\" called with outcome: ");
		Serial.println(result);
	#endif
	return result;
}

const char* LimitSwitch::get_name() {
	return _name;
}