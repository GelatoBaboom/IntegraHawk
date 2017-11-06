// Autopilot.h

#ifndef _AUTOPILOT_h
#define _AUTOPILOT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include "Angle.h"
#else
#include "WProgram.h"
#endif
class Autopilot
{
protected:

public:
	Autopilot();
	void init();
	String Control(Angle ReqAngle, Angle CurrentAngle);
private:
	int getServoPositionX(double ReqAngle, double CurrentAngle);
	void servoMove(int position, char ServoCoor);
};

#endif

