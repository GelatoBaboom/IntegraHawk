#include "giro.h"
Giro g;
void setup() {
	g.init();
}

void loop() {
	
	Serial.println(g.GetAngles()); 
}

