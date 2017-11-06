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
	Angle aReq(0, 0);
	Angle ang = g.GetAngles();
	//Angle aCurr(aCurrO.AngleX, aCurrO.AngleY);
	//quizas para despues tenga que ser asi
	//el while junto con el que pide a la antena si hay act de angulo
	//y si no hay nada desde la antena despues de unos cuantos bucles le dice al autopilot
	//que aterrice
	ang = g.GetAnglesSecure();
	ap.Control(aReq, ang);

}

