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
	if (!checkTransitionZone(ReqAngle, CurrentAngle)) {
		servoPosAlRgt = getServoPositionAlRgt(ReqAngle, CurrentAngle);
		servoPosAlLtf = getServoPositionAlLft(ReqAngle, CurrentAngle);
		servoMove(servoPosAlRgt, 'R');
		servoMove(servoPosAlLtf, 'L');
	}
	//esc provisorio para saber si anda
	servoMove(map(ReqAngle.ESC, 1000, 2000, 0, 180), 'E');
}
int Autopilot::getServoPositionAlRgt(Angle ReqAngle, Angle CurrentAngle)
{
	int angCalcX, angCalcY, servoAng, servoAngX, servoAngY;
	angCalcY = ReqAngle.AngleY - CurrentAngle.AngleY;
	angCalcX = ReqAngle.AngleX - CurrentAngle.AngleX;

	servoAngX = map(angCalcX, _minX, _maxX, _minServoXDif, _maxServoXDif);
	servoAngY = map(angCalcY, _minY, _maxY, _minServoAl, _maxServoAl);
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

	servoAngX = map(angCalcX, _minX, _maxX, _minServoXDif, _maxServoXDif);
	servoAngY = map(angCalcY, _minY, _maxY, _maxServoAl, _minServoAl);
	servoAng = servoAngX + servoAngY;

	if (servoAng > _maxServoAl)servoAng = _maxServoAl;
	if (servoAng < _minServoAl)servoAng = _minServoAl;
	return servoAng;
}
bool Autopilot::checkTransitionZone(Angle ReqAngle, Angle CurrentAngle)
{
	if ((CurrentAngle.AngleY > 90 || CurrentAngle.AngleY < -90) && (CurrentAngle.AngleX > 90 || CurrentAngle.AngleX < -90))
	{
		return true;
	}
	////check if is full pitched
	//if ((CurrentAngle.AngleY > 90 || CurrentAngle.AngleY < -90) && (CurrentAngle.AngleX < 90 || CurrentAngle.AngleX > -90))
	//{
	//	return true;
	//}
	return false;
}
void Autopilot::servoMove(int position, char ServoCoor)
{
	if (ServoCoor == 'R')
	{
		int pos = position + _trimServoRgt;
		if (pos != CurrentPosRgt) {
			//Serial.println("Pos: " + String(CurrentPosX));
			CurrentPosRgt = pos;
			servoAlRgt.write(pos);
		}
	}
	if (ServoCoor == 'L')
	{
		int pos = position + _trimServoLft;
		if (pos != CurrentPosLft) {
			CurrentPosLft = pos;
			servoAlLft.write(pos);
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
