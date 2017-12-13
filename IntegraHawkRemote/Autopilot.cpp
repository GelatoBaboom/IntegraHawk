#include "Autopilot.h"
#include <Servo.h>
Servo servoAlRgt;
Servo servoAlLft;
Servo servoESC;
int CurrentPosRgt;
int CurrentPosLft;
int CurrentPosESC;
Autopilot::Autopilot()
{

}
void Autopilot::init()
{
	servoAlRgt.attach(9);
	servoAlLft.attach(10);
	servoESC.attach(11);
}
void Autopilot::Control(Angle ReqAngle, Angle CurrentAngle)
{
	int servoPosAlRgt, servoPosAlLtf, servoPosESC;
	servoPosAlRgt = getServoPositionAlRgt(ReqAngle, CurrentAngle);
	servoPosAlLtf = getServoPositionAlLft(ReqAngle, CurrentAngle);
	servoMove(servoPosAlRgt, 'R');
	servoMove(servoPosAlLtf, 'L');
	//esc provisorio para saber si anda
	servoMove(map(ReqAngle.ESC, 1000, 2000, 0, 180), 'E');
}
int Autopilot::getServoPositionAlRgt(Angle ReqAngle, Angle CurrentAngle)
{
	int angCalcX, angCalcY, servoAng, servoAngX, servoAngY;
	angCalcY = ReqAngle.AngleY - CurrentAngle.AngleY;
	angCalcX = ReqAngle.AngleX - CurrentAngle.AngleX;

	servoAngX = map(angCalcX, -45, 45, _minServoXDif, _maxServoXDif);
	servoAngY = map(angCalcY, -45, 45, _minServoAl, _maxServoAl);
	servoAng = servoAngX + servoAngY;
	if (servoAng > _maxServoAl)servoAng = _maxServoAl;
	if (servoAng < _minServoAl)servoAng = _minServoAl;
	return servoAng;
}
int Autopilot::getServoPositionAlLft(Angle ReqAngle, Angle CurrentAngle)
{
	int angCalcX, angCalcY, servoAng, servoAngX, servoAngY;
	angCalcX = ReqAngle.AngleX - CurrentAngle.AngleX;
	angCalcY = ReqAngle.AngleY - CurrentAngle.AngleY;

	servoAngX = map(angCalcX, -45, 45, _minServoXDif, _maxServoXDif);
	servoAngY = map(angCalcY, -45, 45, _maxServoAl, _minServoAl);
	servoAng = servoAngX + servoAngY;
	if (servoAng > _maxServoAl)servoAng = _maxServoAl;
	if (servoAng < _minServoAl)servoAng = _minServoAl;
	return servoAng;
}
void Autopilot::servoMove(int position, char ServoCoor)
{
	if (ServoCoor == 'R')
	{
		if (position != CurrentPosRgt) {
			//Serial.println("Pos: " + String(CurrentPosX));
			CurrentPosRgt = position;
			servoAlRgt.write(position);
		}
	}
	if (ServoCoor == 'L')
	{
		if (position != CurrentPosLft) {
			CurrentPosLft = position;
			servoAlLft.write(position);
		}
	}
	if (ServoCoor == 'E')
	{
		if (position != CurrentPosESC) {
			CurrentPosESC = position;
			servoESC.write(position);
		}
	}

}
