#ifndef Motor_h
#define Motor_h

#include "MCP4921.h"
#include "JsonGenerator.h"

class Motor {
public:
	enum speed {
		full_speed = 4096,
		half_speed = 2048,
		zero_speed = 0,
	};

	enum movement {
		move_up,
		move_down,
		stop_moving,
	};

private:
	int _move_down_pin;
	int _move_up_pin;
	MCP4921 *speed_regulator;

	unsigned long _start_time;
	bool _is_moving;

	void move(movement movement, int speed);

public:
	Motor(int down_pin, int up_pin, int SS);

	virtual void up();
	virtual void up(speed speed);
	virtual void up(int speed);

	virtual bool up_with_time(int on_time);
	virtual bool up_with_time(int on_time, speed speed);
	virtual bool up_with_time(int on_time, int speed);

	virtual void down();
	virtual void down(speed speed);
	virtual void down(int speed);

	virtual bool down_with_time(int on_time);
	virtual bool down_with_time(int on_time, speed speed);
	virtual bool down_with_time(int on_time, int speed);

	virtual void stop();

	ArduinoJson::Generator::JsonObject<1> get_json_status();

	
};

#endif