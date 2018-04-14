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
void setup() {
	//Serial.begin(115200);
	ap.init();
	g.init();
	ant.begin(9600);
	pinMode(13, OUTPUT);
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
		pilotTimer = micros();
	}
	else {
		int timeout = ((micros() - pilotTimer) / 1000);
		if (timeout > 1000 && timeout<3000)
		{
			aCurse = Angle(0, 0, 0.0);
			aCurse.ESC = 1000;
		}
		if (timeout > 3000)
		{
			aCurse = Angle(-4, 4, 0.0);
			aCurse.ESC = 1000;
		}
	}

	Angle ang = g.GetAngles();
	if (ang.HasAngle == true) {
		ap.Control(aCurse, ang);
		digitalWrite(13, HIGH);
	}
	//Led Blink 
	if (((micros() - timer) / 500) > 250)
	{
		digitalWrite(13, LOW);
		timer = micros();
	}

}

