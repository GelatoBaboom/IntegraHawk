// CruiseControl.h

#ifndef _CRUISECONTROL_h
#define _CRUISECONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include "Angle.h"
#else
#include "WProgram.h"
#endif

class CruiseControl
{
protected:


public:
	CruiseControl();
	double getCourse(Angle current, double turn);
	Angle getAnglesFromCourse(Angle current, double retCourse);
};


#endif

