#include "LimitSwitch.h"
#include "WaterSensor.h"

#include "Vlonder.h"


/* defines */
#define DEBUG_VIA_SERIAL

#define LIMIT_SWITCH_INTERRUPT_NUMBER 4 // dont know which interrupt number yet
#define REMOTE_CONTROL_INTERRUPT_NUMBER 5 // dont know which interrupt number yet 

/* global flags for interrupt handling */

volatile bool flag_remote_control_button_pressed = false;


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

	setup_ISRs();

	
}

void loop() {
	
	if (flag_remote_control_button_pressed)
		handle_remote_control();


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

void handle_remote_control(void) {

}

void setup_ISRs(void) {
	/*
		int.0 : pin 2
		int.1 : pin 3
		int.2 : pin 21
		int.3 : pin 20
		int.4 : pin 19
		int.5 : pin 18
	*/

	// attach interrupt to all limit switches to occur when the input changes from low to high
	attachInterrupt(LIMIT_SWITCH_INTERRUPT_NUMBER, ISR_limit_switch_reached, RISING);

	// attach interrupt to all remote control buttons to occur when input changes
	attachInterrupt(REMOTE_CONTROL_INTERRUPT_NUMBER, ISR_remote_control, CHANGE);
}


void ISR_limit_switch_reached(void) {
	// dont know yet to do this or global variable and in loop call stop....
	vlonder.stop();
}

void ISR_remote_control(void) {
	// inverses state of this flag.
	flag_remote_control_button_pressed = !flag_remote_control_button_pressed;
}