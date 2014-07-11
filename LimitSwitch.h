#ifndef LimitSwitch_h
#define LimitSwitch_h

class LimitSwitch {

private:
	int _pin;

public:
	LimitSwitch(int pin);
	bool has_reached_limit();
};

#endif