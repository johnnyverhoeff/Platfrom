#ifndef MotorWithBrake_h
#define MotorWithBrake_h

#include "Motor.h"

class MotorWithBrake : public Motor {
private:
	int _brake_pin;
	void _release_brake();
	void _attach_brake();

public:
	MotorWithBrake(int down_pin, int up_pin, int brake_pin, int SDI, int SCK, int CS);

	void up();
	void up(motor_speed speed);
	void up(int speed);

	void down();
	void down(motor_speed speed);
	void down(int speed);

	void stop();
};

#endif