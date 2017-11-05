#include "Autopilot.h"
#include "Angle.h"
#include "Antenna.h"
#include "giro.h"
#include "Antenna.h"
Giro g;
Antenna a;
Autopilot ap;
void setup() {
	//Serial.begin(9600);
	g.init();
	a.begin(9600);

}

void loop() {
	//Serial.println(); 
	a.send(g.GetAngles().toString());

}

