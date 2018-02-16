#include "Angle.h"
#include "Antenna.h"
const int analogPinX = A0;
const int analogPinY = A1;
const int analogPinYCorrection = A3;
const int analogPinESC = A2;
const int buzzPin = 9;

int valueX = 0;
int valueY = 0;
int valueYCorr = 0;
int valueESC = 0;
int posCorrCurrent = 0;
//para pruebas 
uint32_t timer;
//
#include <SoftwareSerial.h>
SoftwareSerial antSerial(2, 3);
void setup() {
	Serial.begin(9600);
	antSerial.begin(9600);
	startToneAlert();
}

void loop() {
	valueX = analogRead(analogPinX);
	valueY = analogRead(analogPinY);
	valueYCorr = analogRead(analogPinYCorrection);
	valueESC = analogRead(analogPinESC);

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
	int actPositionycorr = map(valueYCorr, 0, 1023, -90, 90);
	adjustToneAlert(actPositionycorr);

	//Serial.println(String( actPositionycorr));
	int actPositiony = map((valueY + actPositionycorr), 0, 1023, -126, 126);
	int actPositionESC = map(valueESC, 0, 1023, 126, -126);
	byte buffer[5] = { (char)-127,(char)actPositionx, (char)actPositiony,(char)actPositionESC,(char)127 };

	antSerial.write(buffer, 5);
	delay(50);

}

void adjustToneAlert(int poscorr)
{
	if (posCorrCurrent != poscorr) {
		tone(buzzPin, (poscorr < 0 ? -(poscorr) : poscorr) * 10, 80);
		posCorrCurrent = poscorr;
	}
}

void startToneAlert()
{
	tone(buzzPin, 440, 200);
	delay(150);
	tone(buzzPin, 494, 200);
	delay(150);
	tone(buzzPin, 523, 200);
	delay(150);
	tone(buzzPin, 702, 200);
	delay(500);
}