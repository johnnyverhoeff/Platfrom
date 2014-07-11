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