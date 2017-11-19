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
bool led = false;
bool noPilot = false;
void setup() {
	//Serial.begin(115200);
	g.init();
	ap.init();
	ant.begin(9600);
	pinMode(13, OUTPUT);
}

void loop() {
	String data = ant.receive();
	Angle aReq(data);
	if (aReq.HasAngle == true) {
		aCurse = Angle(aReq.AngleX, aReq.AngleY, 0.0);
		/*
			noPilot = false;
			timer = micros();*/
	}
	else {
		
		/*if (noPilot == false) {
			noPilot = true;
			timer = micros();
		}
		if (((micros() - timer) / 1000000) > 3)
		{
			Serial.println("No hay piloto.. Dios!!");
			timer = micros();
		}
		else
		{
			Serial.println("Tiempo: " + String(timer));
		}*/
	}
	Angle ang = g.GetAnglesSecure();
	//Serial.println(ang.toString());
	ap.Control(aCurse, ang);
	/*if (((micros() - timer) / 1000) > 250)
	{
		led = !led;
		digitalWrite(13, led);
		timer = micros();
	}*/

}

