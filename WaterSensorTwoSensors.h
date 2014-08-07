#include "WaterSensorOneSensor.h"

#ifndef WaterSensorTwoSensors_h
#define WaterSensorTwoSensors_h

class WaterSensorTwoSensors : public WaterSensorOneSensor {
protected:
	int _upper_pin;


public:
	WaterSensorTwoSensors(int lower_pin, int upper_pin, const char* name = "A WaterSensor with two sensors");

	bool is_water_rising();
	bool is_water_dropping();
	bool is_water_steady();

	bool has_reached_position(vlonder_moving_states moving_state);


};

#endif