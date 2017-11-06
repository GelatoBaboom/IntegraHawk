#include "Autopilot.h"
#include "Angle.h"
#include "Antenna.h"
#include "giro.h"
#include "Antenna.h"
Giro g;
Antenna a;
Autopilot ap;
void setup() {
	Serial.begin(115200);
	Serial.println("Inicializacion");
	g.init();
	ap.init();
	a.begin(9600);
	Serial.println("Inicialiced");
}

void loop() {
	//Serial.println();
	Angle aReq(0, 0);

	//Angle aCurr(aCurrO.AngleX, aCurrO.AngleY);
	Angle ang = g.GetAngles();
	if (ang.HasAngle == true) {
		String vals = ang.toString();
		ap.Control(aReq, ang);
		//Serial.println("Valores: " + vals);
	}
	//Serial.println("Servo p: " + ap.Control(aReq, aCurr));
	//a.send(g.GetAngles().toString());


}

