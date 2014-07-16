#ifndef LimitSwitch_h
#define LimitSwitch_h

class LimitSwitch {

private:
	int _pin;
	const char* _name;

public:
	LimitSwitch(int pin, const char *name = "A LimitSwitch");
	bool has_reached_limit();
	const char* get_name();
};

#endif