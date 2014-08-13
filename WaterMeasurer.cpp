#include "WaterMeasurer.h"
#include "Arduino.h"
//#include "HardwareSerial.h"

//#define DEBUG_VIA_SERIAL

WaterMeasurer::WaterMeasurer() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("WaterMeasurer::WaterMeasurer called");
	#endif

	_reset();

	_sample_period = 6;
	_sample_time = 1;
	_motor_on_time = 50;

	_lower_threshold = 10;
	_upper_threshold = 90;
}

void WaterMeasurer::_reset_hits() {
	//#ifdef DEBUG_VIA_SERIAL
		//Serial.println("WaterMeasurer::_reset_hits called");
	//#endif
	_water_dropping_hits = 0;
	_water_rising_hits = 0;
}

void WaterMeasurer::_reset() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("WaterMeasurer::_reset called");
	#endif
	_reset_hits();
	_sample_in_progress = false;
	_sample_counter = 0;
	_total_samples_needed = 10 * _sample_period / _sample_time;
}

bool WaterMeasurer::measure_sample(unsigned long start_time) {
	//#ifdef DEBUG_VIA_SERIAL
		//Serial.println("WaterMeasurer::measure_sample called");
		//Serial.print("start_time: "); Serial.println(start_time);
		//Serial.print("millis(): "); Serial.println(millis());
	//#endif

	if (millis() - start_time < _sample_time * 100) {
		_sample_in_progress = true;
		return false;
	}
	
	_sample_counter++;

	if (active_water_sensor->is_water_dropping())
		_water_dropping_hits++;

	if (active_water_sensor->is_water_rising())
		_water_rising_hits++;

	//#ifdef DEBUG_VIA_SERIAL
		//Serial.print("_water_dropping_hits: "); Serial.println(_water_dropping_hits);
		//Serial.print("_water_rising_hits: "); Serial.println(_water_rising_hits);
	//#endif

	_sample_in_progress = false;
	return true;
}

WaterMeasurer::measure_results WaterMeasurer::get_measure_results() {
	//#ifdef DEBUG_VIA_SERIAL
		//Serial.println("WaterMeasurer::get_measure_results called");
	//#endif
	if (_sample_counter < _total_samples_needed) { // if not done collecting all samples

		if (!_sample_in_progress) // if no sample is in progress, set the start time and call the measure method
			_sample_start_time = millis();

		measure_sample(_sample_start_time);
			
		return undetermined;
	}
	else {
		float water_rising_percentage = _water_rising_hits * 100.0 / _total_samples_needed;
		float water_dropping_percentage = _water_dropping_hits * 100.0 / _total_samples_needed;

		_reset();

		if (water_dropping_percentage <= _lower_threshold && water_rising_percentage >= _upper_threshold) {
			//Serial.println("RESULT MOVING UP");
			return move_up;
		}
			
		else if (water_dropping_percentage >= _upper_threshold && water_rising_percentage <= _lower_threshold) {
			//Serial.println("RESULT MOVING DOWN");
			return move_down;
		}
			
		else
			return stay_at_position;
	}
}

int WaterMeasurer::get_motor_on_time() {
	return _motor_on_time;
}

using namespace ArduinoJson::Generator;

JsonObject<11> WaterMeasurer::get_json_status() {
	JsonObject<11> root;

	root["total_samples"] = _total_samples_needed;

	root["water_rising_hits"] = _water_rising_hits;
	root["water_dropping_hits"] = _water_dropping_hits;

	root["sample_period"] = _sample_period;
	root["sample_time"] = _sample_time;
	root["motor_on_time"] = _motor_on_time;

	root["lower_threshold"] = _lower_threshold;
	root["uppper_theshold"] = _upper_threshold;

	root["sample_in_progress"] = _sample_in_progress;

	root["current_sample"] = _sample_counter;

	return root;
}
