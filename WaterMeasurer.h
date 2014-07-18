#ifndef WaterMeasurer_h
#define WaterMeasurer_h

#include "WaterSensor.h"

class WaterMeasurer {

public:
	enum measure_results {
		undetermined,
		stay_at_position,
		move_up,
		move_down,
	};

private:

	void _reset();
	void _reset_hits();

	int _sample_counter;
	int _total_samples_needed;

	int _water_rising_hits;
	int _water_dropping_hits;

	int _sample_period;	// sample period in seconds
	int _sample_time;	// sample time in 100 mS
	int _motor_on_time; // motor on time in 100 mS

	int _lower_threshold; // thresholds in %
	int _upper_threshold;
	
	bool _sample_in_progress;
	unsigned long _sample_start_time;

	bool measure_sample(unsigned long _start_time);

public:
	WaterMeasurer();

	measure_results get_measure_results();

	WaterSensor *active_water_sensor;
};

#endif