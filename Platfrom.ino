#include "LimitSwitch.h"
#include "WaterSensor.h"

#include "Vlonder.h"

#define DEBUG_VIA_SERIAL

WaterSensor *active_water_sensor;

Vlonder vlonder;

enum program_states {
	none,
	should_reach_a_water_sensor,
};

program_states program_state;

void setup() {
	/* add setup code here */

	Serial.begin(9600);
	program_state = none;
}

void loop() {
	/* add main program code here */


	// selecteren via afstandbediening ISR
	//active_water_sensor = &under_water_sensor;

	switch (program_state) {
		case should_reach_a_water_sensor:
			reach_active_water_sensor();
			break;
		default:
			break;
	}
}

void reach_active_water_sensor() {
	if (!active_water_sensor->has_reached_position(vlonder.get_moving_state()))
	{
		if (active_water_sensor->must_move_up_to_reach_position())
			vlonder.up();
		else
			vlonder.down();
	}
	else
		vlonder.stop();
}