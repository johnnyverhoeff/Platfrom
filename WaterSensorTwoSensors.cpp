#include "WaterSensorTwoSensors.h"
#include "Arduino.h"

WaterSensorTwoSensors::WaterSensorTwoSensors(int lower_pin, int upper_pin) : 
	WaterSensorOneSensor(lower_pin), _upper_pin(upper_pin) {
	pinMode(_pin, INPUT);
	pinMode(_upper_pin, INPUT);
}

bool WaterSensorTwoSensors::is_water_rising() {
	return digitalRead(_pin) && digitalRead(_upper_pin);
}

bool WaterSensorTwoSensors::is_water_dropping() {
	return !digitalRead(_pin) && !digitalRead(_upper_pin);
}

bool WaterSensorTwoSensors::is_water_steady() {
	return digitalRead(_pin) && !digitalRead(_upper_pin);
}