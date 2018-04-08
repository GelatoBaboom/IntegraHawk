#include "Angle.h"
#include "Antenna.h"
const int analogPinX = A0;
const int analogPinY = A1;
const int analogPinYCorrection = A3;
const int analogPinESC = A2;
const int buzzPin = 9;
const int ledPin = 13;

//timer y vals
int valueX = 0;
int valueY = 0;
int valueYCorr = 0;
int valueESC = 0;
int posCorrCurrent = 0;
uint32_t timer;
bool led = false;
//
#include <SoftwareSerial.h>
SoftwareSerial antSerial(2, 3);
void setup() {
	Serial.begin(9600);
	antSerial.begin(9600);
	startToneAlert();
	pinMode(ledPin, OUTPUT);
}

void loop() {
	valueX = analogRead(analogPinX);
	valueY = analogRead(analogPinY);
	valueYCorr = analogRead(analogPinYCorrection);
	valueESC = analogRead(analogPinESC);

	//Led Blink 
	if (((micros() - timer) / 1000) > (led ? 750 : 100))
	{
		led = !led;
		digitalWrite(13, led);
		timer = micros();
	}

	int actPositionx = map(valueX, 0, 1023, 126, -126);
	int actPositionycorr = map(valueYCorr, 0, 1023, -200, 200);
	adjustToneAlert(actPositionycorr);

	//Position y and correction
	int actPositionyAndCorrection = valueY + actPositionycorr;
	actPositionyAndCorrection = actPositionyAndCorrection < 0 ? 0 : actPositionyAndCorrection;
	actPositionyAndCorrection = actPositionyAndCorrection > 1023 ? 1023 : actPositionyAndCorrection;
	int actPositiony = map(actPositionyAndCorrection, 0, 1023, -126, 126);
	//Pos ESC
	int actPositionESC = map(valueESC, 0, 1023, 126, -126);
	byte buffer[5] = {  (char)-127,(char)actPositionx, (char)actPositiony,(char)actPositionESC,(char)127 };

	antSerial.write(buffer, 6);
	delay(50);

}

void adjustToneAlert(int poscorr)
{
	int dif = (posCorrCurrent - poscorr);
	int diffp = (dif < 0 ? -(dif) : dif);
	if (diffp > 3) {

		int p = (poscorr < 0 ? -(poscorr) : poscorr);
		if (p<3 && p>-3) {
			tone(buzzPin, 440, 100);
			delay(150);
			tone(buzzPin, 494, 100);
			delay(150);
			tone(buzzPin, 440, 100);
		}
		else
		{
			tone(buzzPin, (p * 10) + 100, 80);
		}
		posCorrCurrent = poscorr;
	}
}

void startToneAlert()
{
	tone(buzzPin, 440, 150);
	delay(150);
	tone(buzzPin, 494, 150);
	delay(150);
	tone(buzzPin, 523, 150);
	delay(150);
	tone(buzzPin, 528, 200);
	delay(200);
}