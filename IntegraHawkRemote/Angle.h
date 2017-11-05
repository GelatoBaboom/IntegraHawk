// Angle.h

#ifndef _ANGLE_h
#define _ANGLE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
class Angle
{
protected:

public:
	Angle(double x, double y);
	Angle(String xy);
	double AngleX;
	double AngleY;
	String toString();
private:

};

#endif

