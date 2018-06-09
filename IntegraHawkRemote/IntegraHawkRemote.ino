#include "Autopilot.h"
#include "Angle.h"
#include "Antenna.h"
#include "giro.h"
#include "Antenna.h"
Giro g;
Antenna ant;
Autopilot ap;
Angle aCurse(0, 0, 0);
uint32_t timer;
uint32_t pilotTimer;
uint32_t transDelay;
int ledPin = 13;
int buzzPin = 11;

uint32_t cruiserTimer;
double lastCourseZ = 0.0;
double correctionCourseY = 0.0;
bool cruiseDefined = false;

void setup() {
	//Serial.begin(115200);
	ap.init();
	g.init();
	ant.begin(9600);
	pinMode(ledPin, OUTPUT);
}
Angle aReq(0, 0, 0, false);
void loop() {
	if ((micros() - transDelay) / 1000 > 50) {
		aReq = ant.receiveData();
		transDelay = micros();
	}
	if (aReq.HasAngle == true) {
		aCurse = Angle(aReq.AngleX, aReq.AngleY, 0.0);
		aCurse.ESC = aReq.ESC;
		aCurse.Autopilot = aReq.Autopilot;

		pilotTimer = micros();
	}
	else {
		int timeout = ((micros() - pilotTimer) / 1000);
		if (timeout > 1000 && timeout < 3000)
		{
			aCurse = Angle(0, 0, 0.0);
			aCurse.ESC = 1000;
			aCurse.Autopilot = true;
		}
		if (timeout > 3000)
		{
			aCurse = Angle(-4, 4, 0.0);
			aCurse.ESC = 1000;
			aCurse.Autopilot = true;
		}

	}

	Angle ang = g.GetAngles();
	//Led Blink 
	if (((micros() - timer) / 1000) > 500)
	{
		digitalWrite(ledPin, LOW);
		timer = micros();
		if (aReq.HasAngle == false) {
			tone(buzzPin, 528, 250);
		}
	}

}

