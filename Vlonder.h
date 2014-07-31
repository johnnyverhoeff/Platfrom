#include "LimitSwitch.h"
#include "Motor.h"
#include "WaterSensor.h"
#include "WaterMeasurer.h"
#include "Vlonder_enums.h"
#include "HardwareSerial.h"
#include "Arduino.h"

namespace Vlonder {

	//#define DEBUG_VIA_SERIAL

	vlonder_moving_states _moving_state;

	LimitSwitch *_upper_limit_switch;
	LimitSwitch *_lower_limit_switch;

	Motor *_left_motor;
	Motor *_right_motor;

	WaterSensor *active_water_sensor;

	WaterMeasurer water_measurer;



	void Begin() {
		#ifdef DEBUG_VIA_SERIAL
			Serial.println("Vlonder::Vlonder called");
		#endif
		// both limit switches on interrupt pins, dont know which ones yet
		_lower_limit_switch = new LimitSwitch(30);
		_upper_limit_switch = new LimitSwitch(31);

		_left_motor = new Motor(40, 41, 42);
		_right_motor = new Motor(43, 44, 45);
		
		_moving_state = vlonder_stopped;
	}

	void stop() {
		//#ifdef DEBUG_VIA_SERIAL
			Serial.println("Vlonder::stop called");
		//#endif

		_moving_state = vlonder_stopped;
		_left_motor->stop();
		_right_motor->stop();

	}

	void up(int speed) {
		#ifdef DEBUG_VIA_SERIAL
			Serial.print("Vlonder::up called with param: ");
			Serial.println(speed);
		#endif

		if (_upper_limit_switch->has_reached_limit()) {
			stop();
			return;
		}
		_moving_state = vlonder_moving_up;
		_left_motor->up(speed);
		_right_motor->up(speed);
	}

	void up(Motor::speed speed) {
		#ifdef DEBUG_VIA_SERIAL
			Serial.print("Vlonder::up called with param: ");
			Serial.println(speed);
		#endif

		up((int)speed);
	}


	void up() {
		#ifdef DEBUG_VIA_SERIAL
			Serial.println("Vlonder::up called");
		#endif

		up(Motor::full_speed);
	}

	void up_with_time(int on_time, int speed) {
		if (_upper_limit_switch->has_reached_limit()) {
			stop();
			return;
		}

		_moving_state = vlonder_moving_up;

		if (!_left_motor->up_with_time(on_time, speed) &
			!_right_motor->up_with_time(on_time, speed))
			stop();

		delay(10);
	}

	void up_with_time(int on_time, Motor::speed speed) {
		up_with_time(on_time, (int)speed);
	}

	void up_with_time(int on_time) {
		up_with_time(on_time, Motor::full_speed);
	}

	void down(int speed) {
		#ifdef DEBUG_VIA_SERIAL
			Serial.print("Vlonder::down called with param: ");
			Serial.println(speed);
		#endif

		if (_lower_limit_switch->has_reached_limit()) {
			stop();
			return;
		}
		_moving_state = vlonder_moving_down;
		_left_motor->down(speed);
		_right_motor->down(speed);
	}

	void down(Motor::speed speed) {
		#ifdef DEBUG_VIA_SERIAL
			Serial.print("Vlonder::down called with param: ");
			Serial.println(speed);
		#endif

		down((int)speed);
	}

	void down() {
		#ifdef DEBUG_VIA_SERIAL
			Serial.println("Vlonder::down called");
		#endif

		down(Motor::full_speed);
	}

	void down_with_time(int on_time, int speed) {
		if (_lower_limit_switch->has_reached_limit()) {
			stop();
			return;
		}

		_moving_state = vlonder_moving_down;

		if (!_left_motor->down_with_time(on_time, speed) &
			!_right_motor->down_with_time(on_time, speed))
			stop();		

		delay(10);
	}


	void down_with_time(int on_time, Motor::speed speed) {
		down_with_time(on_time, (int)speed);
	}

	void down_with_time(int on_time) {
		down_with_time(on_time, Motor::full_speed);
	}


	vlonder_moving_states get_moving_state() {
		#ifdef DEBUG_VIA_SERIAL
			Serial.print("Vlonder::get_moving_state called with outcome: ");
			Serial.println(_moving_state);
		#endif

		return _moving_state;
	}

	bool reach_active_water_sensor() {
		#ifdef DEBUG_VIA_SERIAL
			Serial.print("Vlonder::reach_active_water_sensor called with active sensor: ");
			Serial.println(active_water_sensor->get_name());
		#endif

		if (!active_water_sensor->has_reached_position(_moving_state))
		{
			if (active_water_sensor->must_move_up_to_reach_position())
				up();
			else
				down();

			return false;
		}
		else
		{
			stop();
			return true;
		}

	}

	void set_active_water_sensor(WaterSensor *sensor) {
		active_water_sensor = sensor;
		water_measurer.active_water_sensor = sensor;
	}

	void control_at_active_water_sensor() {
		#ifdef DEBUG_VIA_SERIAL
			//Serial.print("Vlonder::control_at_active_water_sensor called with active sensor: ");
			//Serial.println(active_water_sensor->get_name());
		#endif


		switch (_moving_state) {
			case vlonder_moving_up:
				up_with_time(water_measurer.get_motor_on_time());
				return;

			case vlonder_moving_down:
				down_with_time(water_measurer.get_motor_on_time());
				return;

			case vlonder_stopped:
			default:
				//Serial.println("switch(_moving_state) -> stopped");
				break;
		}

		switch (water_measurer.get_measure_results()) {
			case WaterMeasurer::move_up:
				up_with_time(water_measurer.get_motor_on_time());
				break;

			case WaterMeasurer::move_down:
				down_with_time(water_measurer.get_motor_on_time());
				break;

			case WaterMeasurer::stay_at_position:
			case WaterMeasurer::undetermined:
			default:
				//Serial.println("switch(water meter) -> un/stay");

				break;
		}
	}
}