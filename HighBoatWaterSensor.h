#include "WaterSensorTwoSensors.h"

#ifndef HighBoatWaterSensor_h
#define HighBoatWaterSensor_h

#define HIGH_BOAT_UPPER_PIN 2 //No idea what number....
#define HIGH_BOAT_LOWER_PIN 3

class HighBoatWaterSensor : public WaterSensorTwoSensors {
public:
	HighBoatWaterSensor() : WaterSensorTwoSensors(HIGH_BOAT_LOWER_PIN, HIGH_BOAT_UPPER_PIN) { }
};

#endif