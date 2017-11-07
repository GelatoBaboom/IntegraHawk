#include "Angle.h"
#include "Antenna.h"
const int analogPinX = A0;
const int analogPinY = A1;
int valueX;
int valueY;
int positionx;
int positiony;
void setup() {
	Serial.begin(9600);
}

void loop() {
	valueX = analogRead(analogPinX);
	valueY = analogRead(analogPinY);
	positionx = map(valueX, 0, 1023, -60, 60);
	positiony = map(valueY, 0, 1023, -60, 60);
	Serial.println("X:" + String(positionx));
	Serial.println("Y:" + String(positiony));
}
