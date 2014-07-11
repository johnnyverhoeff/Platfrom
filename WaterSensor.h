#ifndef WaterSensor_h
#define WaterSensor_h

class WaterSensor {
public:
	virtual bool is_water_rising() = 0;
	virtual bool is_water_dropping() = 0;
	virtual bool is_water_steady() = 0;
};

#endif