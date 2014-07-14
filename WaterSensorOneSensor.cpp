#include "WaterSensorOneSensor.h"
#include "Arduino.h"

WaterSensorOneSensor::WaterSensorOneSensor(int pin) : _pin(pin) {
	pinMode(_pin, INPUT);

	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorOneSensor\" Constructor called with pin: ");
		Serial.println(_pin);
	#endif
}

bool WaterSensorOneSensor::is_water_rising() {
	bool result = digitalRead(_pin);
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorOneSensor::is_water_rising\" called with outcome: ");
		Serial.println(result);
	#endif
	return result;
}

bool WaterSensorOneSensor::is_water_dropping() {
	bool result = !is_water_rising();
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorOneSensor::is_water_dropping\" called with outcome: ");
		Serial.println(result);
	#endif
	return result;
}

bool WaterSensorOneSensor::is_water_steady() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorOneSensor::is_water_steady\" called with outcome: ");
		Serial.println(false);
	#endif
	return false;
}

bool WaterSensorOneSensor::has_reached_position(Vlonder::moving_state moving_state) {
	bool result = false;
	switch (moving_state) {
		case Vlonder::moving_up:
			result = is_water_dropping();
			break;
		case Vlonder::moving_down:
			result = is_water_rising();
			break;
		default:
			result = false;
	}

	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorOneSensor::has_reached_position\" called with param: ");
		Serial.print(moving_state);
		Serial.print(", with outcome: ");
		Serial.println(result);
	#endif

	return result;
}