#include "Angle.h"
#include "Antenna.h"
const int analogPinX = A0;
const int analogPinY = A1;
const int analogPinYCorrection = A3;
const int analogPinESC = A2;
const int buzzPin = 9;
const int ledPin = 13;
const int autopilotpin = 7;

//timer y vals
int valueX = 0;
int valueY = 0;
int valueYCorr = 0;
int valueESC = 0;
int posCorrCurrent = 0;
uint32_t timer;
bool led = false;
int autopilotstate = 0;
//
#include <SoftwareSerial.h>
SoftwareSerial antSerial(2, 3);
void setup() {
	Serial.begin(9600);
	antSerial.begin(9600);
	pinMode(ledPin, OUTPUT);
	startToneAlert();
}

void loop() {
	valueX = analogRead(analogPinX);
	valueY = analogRead(analogPinY);
	valueYCorr = analogRead(analogPinYCorrection);
	valueESC = analogRead(analogPinESC);
	if (autopilotstate != digitalRead(autopilotpin))
	{
		autopilotstate = digitalRead(autopilotpin);
		autopilotTone();
	}

	//Led Blink 
	if (((micros() - timer) / 1000) > (led ? 750 : 250))
	{
		led = !led;
		digitalWrite(13, led);
		timer = micros();
	}

	int actPositionx = map(valueX, 0, 1023, 1, 254);
	int actPositionycorr = map(valueYCorr, 0, 1023, -200, 200);
	adjustToneAlert(actPositionycorr);

	//Position y and correction
	int actPositionyAndCorrection = valueY + actPositionycorr;
	actPositionyAndCorrection = actPositionyAndCorrection < 0 ? 0 : actPositionyAndCorrection;
	actPositionyAndCorrection = actPositionyAndCorrection > 1023 ? 1023 : actPositionyAndCorrection;
	int actPositiony = map(actPositionyAndCorrection, 0, 1023, 1, 254);
	//Pos ESC
	int actPositionESC = map(valueESC, 0, 1023, 254, 1);
	byte buffer[6] = { (char)0,(char)actPositionx, (char)actPositiony,(char)actPositionESC,autopilotstate == HIGH ? (char)1 : (char)254,(char)255 };

	antSerial.write(buffer, 6);
	delay(10);

}
bool warned = false;
void adjustToneAlert(int poscorr)
{
	poscorr = fabs(poscorr);
	//Serial.println(String(poscorr));
	int dif = fabs(poscorr - posCorrCurrent);
	//Serial.println(String(dif));
	if (dif > 10 || poscorr < 5) {
		if (poscorr < 5 && !warned) {
			tone(buzzPin, 494, 100);
			delay(150);
			tone(buzzPin, 494, 100);
			delay(150);
			tone(buzzPin, 494, 100);
			delay(150);
			tone(buzzPin, 494, 100);
			warned = true;
			posCorrCurrent = poscorr;
		}
		else
		{
			if (dif > 10) {
				tone(buzzPin, (poscorr * 10) + 100, 80);
				warned = false;
				posCorrCurrent = poscorr;
			}
		}
		
	}
}

void startToneAlert()
{
	tone(buzzPin, 440, 150);
	delay(155);
	tone(buzzPin, 494, 150);
	delay(155);
	tone(buzzPin, 523, 150);
	delay(155);
	tone(buzzPin, 528, 200);
	delay(800);
}
void autopilotTone()
{
	if (autopilotstate == LOW) {
		tone(buzzPin, 440, 200);
		delay(200);
		tone(buzzPin, 528, 200);
		delay(200);
	}
	else
	{
		tone(buzzPin, 528, 200);
		delay(200);
		tone(buzzPin, 440, 200);
		delay(200);
	}
}