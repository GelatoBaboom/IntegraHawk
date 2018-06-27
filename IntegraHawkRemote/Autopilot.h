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
	int getManualServoPositionAlRgt(Angle ReqAngle);
	int getManualServoPositionAlLft(Angle ReqAngle);
	bool checkTransitionZone(Angle ReqAngle, Angle CurrentAngle);
	void servoMove(int position, char ServoCoor);
	//servos max min angles max is 180 min is 0
	const int _maxServoAl = 120;
	const int _minServoAl = 60;
	const int _maxServoXDif = 30;
	const int _minServoXDif = -30;
	//max is 2000 min is 1000
	const int _maxServoESC = 1000;
	const int _minServoESC = 2000;
	//coreccion por giro max 
	const int _maxAngCorrY = 10;
	//plane angles max min in degrees max min is +-90
	//max min pitch(Y)
	const int _minY = -35;
	const int _maxY = 35;
	//max min roll(X)
	const int _minX = -35;
	const int _maxX = 35;
	//trim adjust
	//+ (val>0) ail down
	const int _trimServoRgt = -7;
	//+ (val>0) ail up
	const int _trimServoLft = 2;
};

#endif

