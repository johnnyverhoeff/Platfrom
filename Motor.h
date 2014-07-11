#ifndef Motor_h
#define Motor_h

class Motor {
private:
	int _move_down_pin;
	int _move_up_pin;

public:
	Motor(int, int);
	void up();
	void down();
	void stop();
};

#endif