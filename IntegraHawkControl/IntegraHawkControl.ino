#include "Angle.h"
#include "Antenna.h"
const int analogPinX = A0;
const int analogPinY = A1;
int valueX;
int valueY;
int positionx;
int positiony;
Antenna ant;
void setup() {
	Serial.begin(9600);
	ant.begin(9600);
}

void loop() {
	valueX = analogRead(analogPinX);
	valueY = analogRead(analogPinY);
	positionx = map(valueX, 0, 1023, 45, -45);
	positiony = map(valueY, 0, 1023, 45, -45);
	Angle a((double)positionx, (double)positiony);
	Serial.println(a.toString());
	ant.send(a.toString());
	delay(300);
}
