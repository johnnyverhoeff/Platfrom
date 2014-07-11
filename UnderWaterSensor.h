#include "WaterSensorOneSensor.h"

#ifndef UnderWaterSensor_h
#define UnderWaterSensor_h

#define UNDER_WATER_SENSOR_PIN 1 //No idea what number....

class UnderWaterSensor : public WaterSensorOneSensor {
public:
	UnderWaterSensor() : WaterSensorOneSensor(UNDER_WATER_SENSOR_PIN) { }
};

#endif