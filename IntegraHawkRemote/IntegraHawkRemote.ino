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
	if (ang.HasAngle == true) {
		//CruiseControl
		if (aCurse.Autopilot == false)
		{
			if (cruiseDefined == false)
			{
				lastCourseZ = ang.AngleZ;
				cruiseDefined = true;
			}

			double retCourse = (lastCourseZ > 0) ? lastCourseZ - 180 : lastCourseZ + 180;

			double diff = retCourse - ang.AngleZ;
			double x = 20.0;
			double y = 7.0;
			bool endRet = false;
			if (diff < 10 && diff > -10)
			{
				x = 0.0;
				y = 0.0;
				endRet = true;
			}
			if (endRet)
			{
				if (((micros() - cruiserTimer) / 1000) > 500)
				{
					cruiserTimer = micros();
					double courseY = y + ang.AngleY;
					correctionCourseY = ((courseY< 0.2 && courseY> -0.2) ? correctionCourseY : (courseY < 0.0) ? correctionCourseY + 3.0 : correctionCourseY - 3.0);
				}
				y = y + correctionCourseY;
			}
			if (ang.AngleZ < lastCourseZ && ang.AngleZ  > retCourse) {
				aCurse = Angle(x, y, 0.0);
				aCurse.ESC = 1450;
			}
			else
			{
				aCurse = Angle(-x, y, 0.0);
				aCurse.ESC = 1450;
			}
		}
		else {
			cruiseDefined = false;
		}
		//end CruiseControl
		ap.Control(aCurse, ang);
		if (ang.AngleY <1 && ang.AngleY>-1) {
			digitalWrite(ledPin, HIGH);
		}
	}


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

