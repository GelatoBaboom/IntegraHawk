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
	int getServoPositionAlRgt(Angle ReqAngle, Angle CurrentAngle);
	int getServoPositionAlLft(Angle ReqAngle, Angle CurrentAngle);
	void servoMove(int position, char ServoCoor);
	int _maxServoAl = 135;
	int _minServoAl = 45;
	int _maxServoXDif = 45;
	int _minServoXDif = -45;
	int _maxServoESC = 1000;
	int _minServoESC = 2000;
};

#endif

