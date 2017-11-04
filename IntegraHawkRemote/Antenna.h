// Antenna.h

#ifndef _ANTENNA_h
#define _ANTENNA_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Antenna
{
protected:


public:
	void init();
	void send(String data);
	String  receive();
private:

};


/*extern AntennaClass Antenna;*/

#endif

