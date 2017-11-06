#include "Autopilot.h"
#include "Angle.h"
#include "Antenna.h"
#include "giro.h"
#include "Antenna.h"
Giro g;
Antenna a;
Autopilot ap;
Angle aCurse(0, 0);
uint32_t timer;
bool noPilot = false;
void setup() {
	Serial.begin(115200);
	Serial.println("Inicializacion");
	g.init();
	ap.init();
	a.begin(9600);
	Serial.println("Inicialiced");
}

void loop() {
	String data = a.receive();
	Angle aReq(data);
	if (aReq.HasAngle == true) {
		aCurse = aReq;
		noPilot = false;
		timer = micros();
	}
	else {
		if (noPilot == false) {
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
		}
	}

	Angle ang = g.GetAngles();
	//Angle aCurr(aCurrO.AngleX, aCurrO.AngleY);
	//quizas para despues tenga que ser asi
	//el while junto con el que pide a la antena si hay act de angulo
	//y si no hay nada desde la antena despues de unos cuantos bucles le dice al autopilot
	//que aterrice
	ang = g.GetAnglesSecure();
	ap.Control(aReq, ang);

}

