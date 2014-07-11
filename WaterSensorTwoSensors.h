#include "WaterSensorOneSensor.h"

#ifndef WaterSensorTwoSensors_h
#define WaterSensorTwoSensors_h

class WaterSensorTwoSensors : public WaterSensorOneSensor {
protected:
	int _upper_pin;

public:
	WaterSensorTwoSensors(int, int);
	bool is_water_rising();
	bool is_water_dropping();
	bool is_water_steady();
};

#endif