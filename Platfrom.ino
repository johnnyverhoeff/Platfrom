#include <JsonParser.h>
#include "Vlonder.h"
#include "WaterSensorTwoSensors.h"
#include "SPI\SPI.h"
#include "ClickButton.h"
#include "Ethernet\Ethernet.h"
#include "WebServer.h"
#include "JsonGenerator.h"

template<class T>
inline Print &operator <<(Print &obj, T arg)
{
	obj.print(arg); return obj;
}


#pragma region Defines

//#define DEBUG_VIA_SERIAL

#define LIMIT_SWITCH_INTERRUPT_NUMBER 4 // dont know which interrupt number yet
#define REMOTE_CONTROL_INTERRUPT_NUMBER 3 // dont know which interrupt number yet 

#define HIGH_BOAT_UPPER_PIN 5 // dont know
#define HIGH_BOAT_LOWER_PIN 6 // dont know

#define LOW_BOAT_UPPER_PIN 5 // dont know
#define LOW_BOAT_LOWER_PIN 6 // dont know

#define UNDER_WATER_PIN 6 // dont know
				
#pragma endregion All defines are declared here

#pragma region Flags

volatile bool flag_remote_control_button_pressed = false;

#ifdef DEBUG_VIA_SERIAL
	volatile bool flag_interrupt = false;
	char* interrupt_msg;
#endif

#pragma endregion All flags for interrupt handling are declared here

#pragma region WaterSensors

#define NUM_OF_WATER_SENSORS 3

WaterSensorTwoSensors high_boat_sensor(HIGH_BOAT_LOWER_PIN, HIGH_BOAT_UPPER_PIN, "High boat water sensor");
WaterSensorTwoSensors low_boat_sensor(LOW_BOAT_LOWER_PIN, LOW_BOAT_UPPER_PIN, "Low boat water sensor");
WaterSensorOneSensor under_water_sensor(UNDER_WATER_PIN, "Under water sensor");

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
	Ethernet.localIP().printTo(Serial);

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

WaterSensor* get_correct_water_sensor(int n) {
	switch (n) {
		case 0:
			return &high_boat_sensor;
		case 1:
			return &low_boat_sensor;
		case 2:
			return &under_water_sensor;
		default:
			return &high_boat_sensor;
	}
}

void welcomePage(WebServer &server, WebServer::ConnectionType type, char *, bool) {

	server.httpSuccess();

	if (type == WebServer::HEAD)
		return;

	P(htmlHead) =
		"<html>"
		"<head>"
		"<meta name = 'viewport' content = 'width=device-width, initial-scale=1'/>"
		"<title>Arduino platform web control</title>"
		"<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js'></script>"
		"<link rel=\"stylesheet\" href=\"//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css\"/>"
		"<link rel=\"stylesheet\" href=\"//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap-theme.min.css\"/>"
		"<script src=\"//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js\"></script>"

		"<script>"

		"function sendProgramStatePost(state) {"
			"$.post('http://192.168.215.177/web_control', 'program_state=' + state, '', '');"
		"}"

		"function sendWaterSensorPost(sensor) {"
			"$.post('http://192.168.215.177/web_control', 'water_sensor=' + sensor, '', '');"
		"}"

		"function reachActiveWaterSensor() {"
			"sendProgramStatePost(1);"
		"}"

		"function reachAndControlVlonderOnActiveWaterSensor() {"
			"sendProgramStatePost(2);"
		"}"

		"function controlVlonderOnActiveWaterSensor() {"
			"sendProgramStatePost(3);"
		"}"

		"function moveToUpperLimitSwitch() {"
			"sendProgramStatePost(4);"
		"}"

		"function moveToLowerLimitSwitch() {"
			"sendProgramStatePost(5);"
		"}"

		"function stop() {"
			"sendProgramStatePost(0);"
		"}"

		"document.onkeydown = checkKey;"

		"function checkKey(e) {"
			"e = e || window.event;"
			"if (e.keyCode == '38')			moveToUpperLimitSwitch();"
			"else if (e.keyCode == '40')	moveToLowerLimitSwitch();"
			"else if (e.keyCode == '27')	stop();"
		"}"

		"function highBoatSensor() {"
			"sendWaterSensorPost(0);"
		"}"

		"function lowBoatSensor() {"
			"sendWaterSensorPost(1);"
		"}"

		"function underWaterSensor() {"
			"sendWaterSensorPost(2);"
		"}"
		

		"</script>"
		"</head>"
		"<body>"
		"<div class='container-fluid'>";

	server.printP(htmlHead);

	


	P(reach_upper_ls_button) = 
		"<button type='button' class='btn btn-success btn-lg' onclick='moveToUpperLimitSwitch();'>"
			"Reach upper limit switch <span class='glyphicon glyphicon-chevron-up'></span>"
		"</button>";

	P(reach_lower_ls_button) = 
		"<button type='button' class='btn btn-success btn-lg' onclick='moveToLowerLimitSwitch();'>"
			"Reach lower limit switch <span class='glyphicon glyphicon-chevron-down'></span>"
		"</button>";

	P(reach_active_water_sensor_button) =
		"<button type='button' class='btn btn-warning btn-lg' onclick='reachActiveWaterSensor();'>"
			"Reach active water sensor"
		"</button>";

	P(control_at_active_water_sensor_button) =
		"<button type='button' class='btn btn-warning btn-lg' onclick='controlVlonderOnActiveWaterSensor();'>"
			"Control vlonder"
		"</button>";

	P(reach_and_control_at_active_water_sensor_button) =
		"<button type='button' class='btn btn-warning btn-lg' onclick='reachAndControlVlonderOnActiveWaterSensor();'>"
			"Reach and control vlonder"
		"</button>";


	P(stop_button) = 
		"<button type='button' class='btn btn-danger btn-lg' onclick='stop();'>"
			"STOP"
		"</button>";

	P(water_sensor_dropdown_button) =
		"<div class='btn-group'>"
			"<button type = 'button' class = 'btn btn-info btn-lg dropdown-toggle' data-toggle = 'dropdown'>"
				"Select water sensor <span class = 'caret'></span>"
			"</button>"
			"<ul class = 'dropdown-menu' role = 'menu'>"
				"<li><a onclick='highBoatSensor();'>High boat sensor</a></li>"
				"<li><a onclick='lowBoatSensor();'>Low boat sensor</a></li>"
				"<li class = 'divider'></li>"
				"<li><a onclick='underWaterSensor();'>Under water sensor</a></li>"
			"</ul>"
		"</div>";


	P(nav_bar) =
		"<nav class='navbar navbar-inverse navbar-default' role='navigation'>"
			"<div class='container-fluid'>"
				"<div class='navbar-header'>"
					"<button type='button' class='navbar-toggle' data-toggle='collapse' data-target='#bs-example-navbar-collapse-1'>"
						"<span class = 'sr-only'>Toggle navigation</span>"
						"<span class = 'icon-bar'></span>"
						"<span class = 'icon-bar'></span>"
						"<span class = 'icon-bar'></span>"
					"</button>"
					"<a class='navbar-brand' href='#'>Platform</a>"
				"</div>"

				"<div class = 'collapse navbar-collapse' id = 'bs-example-navbar-collapse-1'>"
					"<ul class = 'nav navbar-nav'>"
						"<li class='active'><a data-toggle='tab' href = '#Tab-RemoteControl'>Remote Control</a></li>" // maybe do somethin with class='active'
						"<li><a data-toggle='tab' href = '#Tab-Information'>Information</a></li>"
					"</ul>"
				"</div><!-- / .navbar - collapse-->"
			"</div><!-- / .container - fluid-->"
		"</nav>"
		;


	P(tabs_part1) =
		"<div class='tabbable'>"
			"<ul class='nav nav-tabs'>"
				"<li class='active'><a data-toggle='tab' href='#Tab-RemoteControl'>Remote Control</a></li>"
				"<li><a data-toggle='tab' href='#Tab-Information'>Information</a></li>"
			"</ul>"

			"<div class='tab-content'>"
				"<div class='tab-pane active' id='Tab-RemoteControl'>";
	P(tabs_part2) =
				"</div>"

				"<div class='tab-pane' id='Tab-Information'>";
	P(tabs_part3) =
				"</div>"
				

			"</div>"

		"</div>"
		;
	

	server.printP(nav_bar);
	//server.printP(tabs_part1);

	server << F("<div class='tab-content'>");
		server << F("<div class='tab-pane active' id='Tab-RemoteControl'> ");
			server << F("<div class='btn-group-vertical'>");
				server.printP(reach_upper_ls_button);
				server.printP(reach_lower_ls_button);
				server.printP(reach_and_control_at_active_water_sensor_button);
				server.printP(reach_active_water_sensor_button);
				server.printP(control_at_active_water_sensor_button);
				server.printP(water_sensor_dropdown_button);
				server.printP(stop_button);
			server << F("</div>");
		server << F("</div>");

		server << F("<div class='tab-pane' id='Tab-Information'>Other stuffff</div>");
	server << F("</div>");

	//server.printP(tabs_part2);
	//server << F("other information");
	//server.printP(tabs_part3);




	server << "</div></body></html>";
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

	
	JsonObject<10> root;

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

	JsonObject<15> root = Vlonder::water_measurer.get_json_status();

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
		Serial.print(name); Serial.println(value);
		if (!strcmp(name, "program_state"))
			if (program_state != remote_control_manual_down && program_state != remote_control_manual_up) {
				program_states desired_state = (program_states)atoi(value);
				if (desired_state >= none && desired_state <= remote_control_manual_down)
					program_state = desired_state;
				else {
					server.httpFail();
					return;
				}
			} 
			else {
				server.httpFail();
				return;
			}


		else if (!strcmp(name, "water_sensor")) {
			int desired_sensor = atoi(value);
			if (desired_sensor >= 0 && desired_sensor < NUM_OF_WATER_SENSORS)
				Vlonder::set_active_water_sensor(get_correct_water_sensor(desired_sensor));
			else {
				server.httpFail();
				return;
			}
				
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