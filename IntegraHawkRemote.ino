#include "giro.h"
Giro g;
void setup() {
	g.init();
	Serial.begin(9600);
}

void loop() {
	
	Serial.println(g.GetAngles()); 
}

