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
	Angle(int x, int y);
	int AngleX;
	int AngleY;
	String toString();
private:

};

#endif

