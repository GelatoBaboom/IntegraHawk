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
	void Control(Angle ReqAngle, Angle CurrentAngle);
private:
	int getServoPositionX(double ReqAngle, double CurrentAngle);
	int getServoPositionY(double ReqAngle, double CurrentAngle, bool StrictMode);
	int getServoPositionZ(int PositionX);
	void servoMove(int position, char ServoCoor);
	int _maxServoX = 180;
	int _minServoX = 0;
	int _maxServoY = 180;
	int _minServoY = 0;
	int _maxServoZ = 117;
	int _minServoZ = 63;
};

#endif

