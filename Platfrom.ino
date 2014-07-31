#include "Vlonder.h"
#include "WaterSensorTwoSensors.h"
#include "SPI\SPI.h"

#pragma region Defines

//#define DEBUG_VIA_SERIAL

#define LIMIT_SWITCH_INTERRUPT_NUMBER 4 // dont know which interrupt number yet
#define REMOTE_CONTROL_INTERRUPT_NUMBER 5 // dont know which interrupt number yet 

#define HIGH_BOAT_UPPER_PIN 10 // dont know
#define HIGH_BOAT_LOWER_PIN 11 // dont know
				
#pragma endregion All defines are declared here

#pragma region Flags

volatile bool flag_remote_control_button_pressed = false;

#ifdef DEBUG_VIA_SERIAL
	volatile bool flag_interrupt = false;
	char* interrupt_msg;
#endif

#pragma endregion All flags for interrupt handling are declared here

#pragma region WaterSensors

WaterSensorTwoSensors high_boat_sensor(HIGH_BOAT_LOWER_PIN, HIGH_BOAT_UPPER_PIN, "High boat water sensor");

#pragma endregion All available water sensors are declared here


enum program_states {
	none,
	reach_active_water_sensor,
	reach_and_control_vlonder_on_active_water_sensor,
	control_vlonder_on_active_water_sensor,
};

program_states program_state;

void setup() {
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);

	Serial.begin(9600);

	Serial.println("Serial has begun");

	program_state = none;
	Vlonder::Begin();

	setup_ISRs();
}

void loop() {
	#ifdef DEBUG_VIA_SERIAL
		if (flag_interrupt) {
			Serial.println(interrupt_msg);
			flag_interrupt = false;
		}
	#endif

	if (flag_remote_control_button_pressed)
		handle_remote_control();
	
	switch (program_state) {

		case reach_active_water_sensor:
			if (Vlonder::reach_active_water_sensor())
				program_state = none;
			break;

		case reach_and_control_vlonder_on_active_water_sensor:
			if (Vlonder::reach_active_water_sensor())
				program_state = control_vlonder_on_active_water_sensor;
			break;

		case control_vlonder_on_active_water_sensor:
			Vlonder::control_at_active_water_sensor();
			break;

		case none: 
		default:
			Vlonder::stop();
			break;
	}
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
	#ifdef DEBUG_VIA_SERIAL
		flag_interrupt = true;
		interrupt_msg = "ISR_limit_switch_reached";
	#endif

	// dont know yet to do this or global variable and in loop call stop....
	Vlonder::stop();
}

void ISR_remote_control(void) {
	#ifdef DEBUG_VIA_SERIAL
		flag_interrupt = true;
		interrupt_msg = "ISR_remote_control";
	#endif

	// inverses state of this flag.
	flag_remote_control_button_pressed = !flag_remote_control_button_pressed;
}