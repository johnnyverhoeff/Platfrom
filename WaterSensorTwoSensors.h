#include "WaterSensorOneSensor.h"

#ifndef WaterSensorTwoSensors_h
#define WaterSensorTwoSensors_h

class WaterSensorTwoSensors : public WaterSensorOneSensor {
protected:
	int _upper_pin;

public:
	WaterSensorTwoSensors(int lower_pin, int upper_pin);

	bool is_water_rising();
	bool is_water_dropping();
	bool is_water_steady();

	bool has_reached_position(Vlonder::moving_state moving_state);
};

#endif