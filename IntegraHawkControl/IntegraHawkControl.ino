#include "Angle.h"
#include "Antenna.h"
const int analogPinX = A0;
const int analogPinY = A1;
int valueX = 0;
int valueY = 0;
int positionx;
int positiony;
//para pruebas 
uint32_t timer;
//
#include <SoftwareSerial.h>
SoftwareSerial antSerial(2, 3);
void setup() {
	Serial.begin(9600);
	antSerial.begin(9600);
}

void loop() {
	valueX = analogRead(analogPinX);
	valueY = analogRead(analogPinY);
	/*if (((micros() - timer) / 1000) > 2000)
	{
		valueX = valueX > 0 ? 0 : 1023;
		timer = micros();
	}*/
	//int actPositionx = map(valueX, 0, 1023, 45, -45);
	//int actPositiony = map(valueY, 0, 1023, -45, 45);
	//positionx = actPositionx;
	//positiony = actPositiony;
	//Angle a((double)positionx, (double)positiony, 0.0);
	////Serial.println(a.toString());
	//antSerial.println(a.toString());

	int actPositionx = map(valueX, 0, 1023, 126, -126);
	int actPositiony = map(valueY, 0, 1023, -126, 126);
	positionx = actPositionx;
	positiony = actPositiony;
	//Serial.println(a.toString());
	byte buffer[4] = { (char)-127,(char)actPositionx, (char)actPositiony,(char)127 };
	antSerial.write(buffer, 4);
	delay(80);

}
