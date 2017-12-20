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
	bool checkTransitionZone(Angle ReqAngle, Angle CurrentAngle);
	void servoMove(int position, char ServoCoor);
	//servos max min angles
	const int _maxServoAl = 135;
	const int _minServoAl = 45;
	const int _maxServoXDif = 45;
	const int _minServoXDif = -45;
	const int _maxServoESC = 1000;
	const int _minServoESC = 2000;
	//plane angles max min in degrees
	//max min pitch(Y)
	const int _minY = -45;
	const int _maxY = 45;
	//max min roll(X)
	const int _minX = -45;
	const int _maxX = 45;
	//trim adjust
	//+ (val>0) ail down
	const int _trimServoRgt = -1;
	//+ (val>0) ail up
	const int _trimServoLft = 2;
};

#endif

