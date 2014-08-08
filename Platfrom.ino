#include "Vlonder.h"
#include "WaterSensorTwoSensors.h"
#include "SPI\SPI.h"
#include "ClickButton.h"
#include "Ethernet\Ethernet.h"
#include "WebServer.h"
#include "JsonGenerator.h"


#pragma region Defines

//#define DEBUG_VIA_SERIAL

#define LIMIT_SWITCH_INTERRUPT_NUMBER 4 // dont know which interrupt number yet
#define REMOTE_CONTROL_INTERRUPT_NUMBER 3 // dont know which interrupt number yet 

#define HIGH_BOAT_UPPER_PIN 5 // dont know
#define HIGH_BOAT_LOWER_PIN 6 // dont know
				
#pragma endregion All defines are declared here

#pragma region Flags

volatile bool flag_remote_control_button_pressed = false;

#ifdef DEBUG_VIA_SERIAL
	volatile bool flag_interrupt = false;
	char* interrupt_msg;
#endif

#pragma endregion All flags for interrupt handling are declared here

#pragma region WaterSensors

#define NUM_OF_WATER_SENSORS 2
WaterSensorTwoSensors high_boat_sensor(HIGH_BOAT_LOWER_PIN, HIGH_BOAT_UPPER_PIN, "High boat water sensor");
WaterSensorOneSensor under_water_sensor(HIGH_BOAT_LOWER_PIN, "Under water sensor");

WaterSensorOneSensor water_sensors[] = { high_boat_sensor, under_water_sensor };



#pragma endregion All available water sensors are declared here

#pragma region WebServer

static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

static uint8_t ip[] = { 192, 168, 215, 177 };

#define PREFIX ""
WebServer webserver(PREFIX, 80);

#pragma endregion All webserver related things are declared here



enum program_states {
	none,

	reach_active_water_sensor,
	reach_and_control_vlonder_on_active_water_sensor,
	control_vlonder_on_active_water_sensor,

	reach_upper_limit_switch,
	reach_lower_limit_switch,

	remote_control_manual_up,
	remote_control_manual_down,
};

program_states program_state;

ClickButton buttons[] = { ClickButton(2, HIGH), ClickButton(3, HIGH) };

void setup() {
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);

	Serial.begin(9600);

	Serial.println("Serial has begun");
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("DEBUG_VIA_SERIAL");
	#endif

	Ethernet.begin(mac, ip);
	setup_WebServer_Commands();

	program_state = control_vlonder_on_active_water_sensor;
	Vlonder::Begin();

	//setup_ISRs();

	Vlonder::set_active_water_sensor(&high_boat_sensor);
}

void loop() {
	#ifdef DEBUG_VIA_SERIAL
		if (flag_interrupt) {
			Serial.println(F("an interrupt"));
			flag_interrupt = false;
		}
	#endif


	char buff[64];
	int len = 64;

	webserver.processConnection(buff, &len);

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

		case reach_upper_limit_switch:
			if (Vlonder::reach_upper_limit_switch())
				program_state = none;
			break;

		case reach_lower_limit_switch:
			if (Vlonder::reach_lower_limit_switch())
				program_state = none;
			break;

		case remote_control_manual_up:
			Vlonder::up();
			break;

		case remote_control_manual_down:
			Vlonder::down();
			break;

		case none: 
		default:
			Vlonder::stop();
			break;
	}
}

void handle_remote_control(void) {
	for (int i = 0; i < 2; i++)
		buttons[i].Update();

	if (buttons[0].clicks == -1)
		program_state = remote_control_manual_up;

	if (program_state == remote_control_manual_up & !buttons[0].depressed)
		program_state = none;

	if (buttons[1].clicks == -1)
		program_state = remote_control_manual_down;

	if (program_state == remote_control_manual_down & !buttons[1].depressed)
		program_state = none;


	if (buttons[0].clicks == -2)
		program_state = reach_upper_limit_switch;

	if (buttons[1].clicks == -2)
		program_state = reach_lower_limit_switch;


	if (buttons[0].clicks == 3)
		Vlonder::set_active_water_sensor(&under_water_sensor);

	if (buttons[1].clicks == 3)
		program_state = control_vlonder_on_active_water_sensor;

}

bool remote_control_is_being_used() {
	return program_state == remote_control_manual_down || program_state == remote_control_manual_up;
}


void welcomePage(WebServer &server, WebServer::ConnectionType type, char *, bool) {

	server.httpSuccess();

	if (type != WebServer::HEAD) {
		P(helloMsg) = "<h1>Arduino platform controller</h1>";
		server.printP(helloMsg);

		server.print(F("<p>Current program state is : ")); server.print(program_state); server.println(F("</p>"));

		server.print(F("<p>Upper Limit Switch: ")); server.print(Vlonder::_upper_limit_switch->has_reached_limit()); server.print(F("</p>"));
		server.print(F("<p>Lower Limit Switch: ")); server.print(Vlonder::_lower_limit_switch->has_reached_limit()); server.print(F("</p>"));
	}

}

void jsonCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
	if (type == WebServer::POST) {
		server.httpFail();
		return;
	}

	server.httpSuccess("application/json");

	if (type == WebServer::HEAD)
		return;

	
	using namespace ArduinoJson::Generator;

	JsonObject<2> button_states;

	button_states["Button0"] = (bool)buttons[0].depressed;
	button_states["Button1"] = (bool)buttons[1].depressed;

	
	JsonObject<3> root;

	root["program_state"] = program_state;
	root["buttons"] = button_states;
	root["vlonder"] = Vlonder::get_json_status();

	root.printTo(server);
}

void water_measurer_cmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
	if (type == WebServer::POST) {
		server.httpFail();
		return;
	}

	server.httpSuccess("application/json");

	if (type == WebServer::HEAD)
		return;

	using namespace ArduinoJson::Generator;

	JsonObject<11> root = Vlonder::water_measurer.get_json_status();

	root.printTo(server);

}

void web_control_cmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete) {
	if (type != WebServer::POST) {
		server.httpFail();
		return;
	}
	
	#define BUFFER_LENGTH 16

	bool repeat;
	char name[BUFFER_LENGTH], value[BUFFER_LENGTH];

	do {
		repeat = server.readPOSTparam(name, BUFFER_LENGTH, value, BUFFER_LENGTH);

		if (!strcmp(name, "program_state"))
			if (remote_control_is_being_used) {
				program_states desired_state = (program_states)atoi(value);
				if (desired_state >= none && desired_state <= remote_control_manual_down)
					program_state = desired_state;
				else
					server.httpFail();
			}
			else
				server.httpFail();

		else if (!strcmp(name, "water_sensor")) {
			int desired_sensor = atoi(value);
			if (desired_sensor >= 0 && desired_sensor < NUM_OF_WATER_SENSORS)
				Vlonder::set_active_water_sensor(&water_sensors[desired_sensor]);
			else
				server.httpFail();
		}
	} while (repeat);

	server.httpSuccess();
}

void setup_WebServer_Commands() {
	webserver.setDefaultCommand(&welcomePage);
	webserver.addCommand("index.html", &welcomePage);

	webserver.addCommand("web_control", &web_control_cmd);

	webserver.addCommand("json", &jsonCmd);
	webserver.addCommand("water_measurer", &water_measurer_cmd);

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
	attachInterrupt(REMOTE_CONTROL_INTERRUPT_NUMBER, ISR_remote_control, RISING);
}


void ISR_limit_switch_reached(void) {
	#ifdef DEBUG_VIA_SERIAL
		flag_interrupt = true;
		//interrupt_msg = "ISR_limit_switch_reached";
	#endif

	Vlonder::stop();
	program_state = none;
}

void ISR_remote_control(void) {
	#ifdef DEBUG_VIA_SERIAL
		flag_interrupt = true;
		//interrupt_msg = "ISR_remote_control";
	#endif

		//Vlonder::stop(); 
		//program_state = none;

	// inverses state of this flag.
	//flag_remote_control_button_pressed = !flag_remote_control_button_pressed;
}