#ifndef WaterSensor_h
#define WaterSensor_h

#include "Vlonder_enums.h"

class WaterSensor {
private:
	const char* _name;
public:
	virtual bool is_water_rising() = 0;
	virtual bool is_water_dropping() = 0;
	virtual bool is_water_steady() = 0;

	virtual bool has_reached_position(vlonder_moving_states moving_state) = 0;
	bool must_move_up_to_reach_position() { return is_water_rising(); }

	const char* get_name() { return _name; }
};

#endif