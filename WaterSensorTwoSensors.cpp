#include "WaterSensorTwoSensors.h"
#include "Arduino.h"

WaterSensorTwoSensors::WaterSensorTwoSensors(int lower_pin, int upper_pin, const char* name) : 
	WaterSensorOneSensor(lower_pin, name), _upper_pin(upper_pin) {
	pinMode(_pin, INPUT);
	pinMode(_upper_pin, INPUT);

	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorTwoSensor\" Constructor called with pins: ");
		Serial.print(_pin); Serial.print(" and "); Serial.println(_upper_pin);
	#endif
}

bool WaterSensorTwoSensors::is_water_rising() {
	bool result = digitalRead(_pin) && digitalRead(_upper_pin);
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorTwoSensor::is_water_rising\" called with outcome: ");
		Serial.println(result);
	#endif
	return result;
}

bool WaterSensorTwoSensors::is_water_dropping() {
	bool result = !digitalRead(_pin) && !digitalRead(_upper_pin);
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorTwoSensor::is_water_dropping\" called with outcome: ");
		Serial.println(result);
	#endif
	return result;
}

bool WaterSensorTwoSensors::is_water_steady() {
	bool result = digitalRead(_pin) && !digitalRead(_upper_pin);
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorTwoSensor::is_water_steady\" called with outcome: ");
		Serial.println(result);
	#endif
	return result;
}

bool WaterSensorTwoSensors::has_reached_position(vlonder_moving_states moving_state) {
	bool result = is_water_steady();
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"WaterSensorTwoSensor::has_reached_position\" called with param: ");
		Serial.print(moving_state);
		Serial.print(", with outcome: ");
		Serial.println(result);
	#endif
	return result;
}