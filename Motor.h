#ifndef LimitSwitch_h
#define LimitSwitch_h

class Motor {
public:
	virtual void up() = 0;
	virtual void down() = 0;
};

#endif