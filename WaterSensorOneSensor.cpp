#include "WaterSensorOneSensor.h"
#include "Arduino.h"

WaterSensorOneSensor::WaterSensorOneSensor(int pin) : _pin(pin) {
	pinMode(_pin, INPUT);
}

bool WaterSensorOneSensor::is_water_rising() {
	return digitalRead(_pin);
}

bool WaterSensorOneSensor::is_water_dropping() {
	return !is_water_rising();
}

bool WaterSensorOneSensor::is_water_steady() {
	return false;
}

bool WaterSensorOneSensor::has_reached_position(Vlonder::moving_state moving_state) {
	switch (moving_state) {
		case Vlonder::moving_up:
			return is_water_dropping();
			break;
		case Vlonder::moving_down:
			return is_water_rising();
			break;
		default:
			return false;
	}
}