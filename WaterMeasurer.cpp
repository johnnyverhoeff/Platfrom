#include "WaterMeasurer.h"
#include "Arduino.h"

WaterMeasurer::WaterMeasurer() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("WaterMeasurer::WaterMeasurer called");
	#endif

	_reset();

	_sample_period = 60;
	_sample_time = 1;
	_motor_on_time = 7;

	_lower_threshold = 10;
	_upper_threshold = 90;
}

void WaterMeasurer::_reset_hits() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("WaterMeasurer::_reset_hits called");
	#endif
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
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("WaterMeasurer::measure_sample called");
	#endif

	if (millis() - start_time < _sample_time * 100) {
		_sample_in_progress = true;
		return false;
	}
	
	_sample_counter++;

	if (active_water_sensor->is_water_dropping())
		_water_dropping_hits++;

	if (active_water_sensor->is_water_rising())
		_water_rising_hits++;

	_sample_in_progress = false;
	return true;
}

WaterMeasurer::measure_results WaterMeasurer::get_measure_results() {
	#ifdef DEBUG_VIA_SERIAL
		Serial.println("WaterMeasurer::get_measure_results called");
	#endif
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

		if (water_dropping_percentage < _lower_threshold && water_rising_percentage < _lower_threshold)
			return move_down;

		else if (water_dropping_percentage > _upper_threshold && water_rising_percentage > _upper_threshold)
			return move_up;

		else
			return stay_at_position;
	}
}
