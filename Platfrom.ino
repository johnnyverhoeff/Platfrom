#include "LimitSwitch.h"
#include "WaterSensor.h"
#include "LowBoatWaterSensor.h"
#include "HighBoatWaterSensor.h"
#include "UnderWaterSensor.h"

WaterSensor *active_water_sensor;

UnderWaterSensor under_water_sensor;
HighBoatWaterSensor high_sensor;
LowBoatWaterSensor low_sensor;

void setup() {
  /* add setup code here */

}

void loop() {
	/* add main program code here */
	active_water_sensor = &under_water_sensor;
	
}
