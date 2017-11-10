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
	int actPositionx = map(valueX, 0, 1023, 45, -45);
	int actPositiony = map(valueY, 0, 1023, -45, 45);
	positionx = actPositionx;
	positiony = actPositiony;
	Angle a((double)positionx, (double)positiony, 0.0);
	Serial.println(a.toString());
	ant.send(a.toString());
	delay(50);
}
