#ifndef LimitSwitch_h
#define LimitSwitch_h

class LimitSwitch {

private:
	int _pin;

public:
	LimitSwitch(int);
	bool has_reached_limit();
};

#endif