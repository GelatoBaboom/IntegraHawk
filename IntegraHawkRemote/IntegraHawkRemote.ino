#include "Angle.h"
#include "Antenna.h"
#include "giro.h"
#include "Antenna.h"
Giro g;
Antenna a;
void setup() {
	g.init();
	a.init();
	Serial.begin(9600);

}

void loop() {
	
	Serial.println(g.GetAngles().toString()); 
	a.receive();
}

