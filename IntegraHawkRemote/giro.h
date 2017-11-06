// giro.h

#ifndef _GIRO_h
#define _GIRO_h
#define degconvert 57.2957786 //there are like 57 degrees in a radian.

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include "Angle.h"
#else
#include "WProgram.h"
#endif

class Giro
{
protected:


public:
	Giro();
	void init();
	Angle GetAngles();
private:
	
};

/*extern GiroClass Giro;*/

#endif

