#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int down_pin, int up_pin, int SS) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"Motor::Motor called with params: down_pin: ");
		Serial.print(down_pin); Serial.print(", up_pin: "); Serial.println(up_pin);
	#endif

	_move_down_pin = down_pin;
	_move_up_pin = up_pin;

	pinMode(_move_up_pin, OUTPUT);
	pinMode(_move_down_pin, OUTPUT);

	digitalWrite(_move_up_pin, LOW);
	digitalWrite(_move_down_pin, LOW);

	speed_regulator = new MCP4921(SS);
	speed_regulator->setValue(zero_speed);

	_is_moving = false;
}

void Motor::move(movement movement, int speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"Motor::move called with params: movement: ");
		Serial.print(movement); Serial.print(", speed: "); Serial.println(speed);
	#endif

	switch (movement) {
		case move_up:
			digitalWrite(_move_up_pin, HIGH);
			digitalWrite(_move_down_pin, LOW);
			_is_moving = true;
			break;
		case move_down:
			digitalWrite(_move_up_pin, LOW);
			digitalWrite(_move_down_pin, HIGH);
			_is_moving = true;
			break;
		case stop_moving: default:
			digitalWrite(_move_up_pin, LOW);
			digitalWrite(_move_down_pin, LOW);	
			_is_moving = false;
			//Serial.print("a motor stopped after: "); Serial.println((millis() - _start_time));
	}

	speed_regulator->setValue(speed);
}

void Motor::down() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("\"Motor::down called");
	#endif

	down(full_speed);
}

void Motor::down(speed speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"Motor::down called with params: speed: ");
		Serial.print(speed);
	#endif

	down((int)speed);
}

void Motor::down(int speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"Motor::down called with params: speed: ");
		Serial.print(speed);
	#endif

	move(move_down, speed);
}

bool Motor::down_with_time(int on_time) {
	return down_with_time(on_time, full_speed);
}

bool Motor::down_with_time(int on_time, speed speed) {
	return down_with_time(on_time, (int)speed);
}

bool Motor::down_with_time(int on_time, int speed) {
	if (!_is_moving) {
		_is_moving = true;
		_start_time = millis();
		move(move_down, speed);
	}
	else if (millis() - _start_time >= on_time * 100) 
		move(stop_moving, zero_speed);

	return _is_moving;
}

void Motor::up() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("\"Motor::up called");
	#endif

	up(full_speed);
}

void Motor::up(speed speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"Motor::up called with params: speed: ");
		Serial.print(speed);
	#endif

	up((int)speed);
}

void Motor::up(int speed) {
	#ifdef DEBUG_VIA_SERIAL
		Serial.print("\"Motor::up called with params: speed: ");
		Serial.print(speed);
	#endif

	move(move_up, speed);
}

bool Motor::up_with_time(int on_time) {
	return up_with_time(on_time, full_speed);
}

bool Motor::up_with_time(int on_time, speed speed) {
	return up_with_time(on_time, (int)speed);
}

bool Motor::up_with_time(int on_time, int speed) {
	if (!_is_moving) {
		_is_moving = true;
		_start_time = millis();
		move(move_up, speed);
	}
	else if (millis() - _start_time >= on_time * 100)
		move(stop_moving, zero_speed);

	return _is_moving;
}


void Motor::stop() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("\"Motor::stop called");
	#endif

	move(stop_moving, zero_speed);
}

ArduinoJson::Generator::JsonObject<1> Motor::get_json_status() {
	ArduinoJson::Generator::JsonObject<1> root;
	root["is_moving"] = _is_moving;

	return root;
}