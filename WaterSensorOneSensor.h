#include "WaterSensor.h"

#ifndef WaterSensorOneSensor_h
#define WaterSensorOneSensor_h

class WaterSensorOneSensor : public WaterSensor {
protected:
	int _pin;

public:
	WaterSensorOneSensor(int pin);

	bool is_water_rising();
	bool is_water_dropping();
	bool is_water_steady();

	bool has_reached_position(Vlonder::moving_state moving_state);
};

#endif