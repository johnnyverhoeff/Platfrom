#include "WaterSensor.h"

#ifndef WaterSensorOneSensor_h
#define WaterSensorOneSensor_h

class WaterSensorOneSensor : public WaterSensor {
protected:
	int _pin;
	const char* _name;

public:
	WaterSensorOneSensor(int pin, const char* name = "A WaterSensor with one sensor");

	bool is_water_rising();
	bool is_water_dropping();
	bool is_water_steady();

	bool has_reached_position(vlonder_moving_states moving_state);
};

#endif