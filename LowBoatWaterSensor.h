#include "WaterSensorTwoSensors.h"

#ifndef LowBoatWaterSensor_h
#define LowBoatWaterSensor_h

#define LOW_BOAT_UPPER_PIN 4 //No idea what number....
#define LOW_BOAT_LOWER_PIN 5

class LowBoatWaterSensor : public WaterSensorTwoSensors {
public:
	LowBoatWaterSensor() : WaterSensorTwoSensors(LOW_BOAT_LOWER_PIN, LOW_BOAT_UPPER_PIN) { }
};

#endif