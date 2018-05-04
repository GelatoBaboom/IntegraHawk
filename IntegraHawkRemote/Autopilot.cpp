#include "Autopilot.h"
#include "Antenna.h"
#include <Servo.h>
Servo servoAlRgt;
Servo servoAlLft;
Servo servoESC;
int CurrentPosRgt;
int CurrentPosLft;
//ESC
int CurrentPosESC;
int minPulseRate = 1000;
int maxPulseRate = 2000;
Autopilot::Autopilot()
{

}
void Autopilot::init()
{
	servoAlRgt.attach(9);
	servoAlLft.attach(10);
	servoESC.attach(6, minPulseRate, maxPulseRate);
	servoESC.writeMicroseconds(1000);
	delay(3000);
	servoESC.writeMicroseconds(1100);
	delay(1000);
	servoESC.writeMicroseconds(1000);
}
void Autopilot::Control(Angle ReqAngle, Angle CurrentAngle)
{
	int servoPosAlRgt, servoPosAlLtf, servoPosESC;
	//if (checkTransitionZone(ReqAngle, CurrentAngle) || ReqAngle.Autopilot == false) {
	if (checkTransitionZone(ReqAngle, CurrentAngle) ) {
		servoPosAlRgt = getManualServoPositionAlRgt(ReqAngle);
		servoPosAlLtf = getManualServoPositionAlLft(ReqAngle);
	}
	else
	{
		servoPosAlRgt = getServoPositionAlRgt(ReqAngle, CurrentAngle);
		servoPosAlLtf = getServoPositionAlLft(ReqAngle, CurrentAngle);

	}
	//Writting servo position
	servoMove(servoPosAlRgt, 'R');
	servoMove(servoPosAlLtf, 'L');
	//esc 
	servoMove(ReqAngle.ESC, 'E');
}
//Automanaged servo position
int Autopilot::getServoPositionAlRgt(Angle ReqAngle, Angle CurrentAngle)
{
	int angCalcX, angCalcY, servoAng, servoAngX, servoAngY;
	//correccion por giro
	int corrY = map(fabs(ReqAngle.AngleX), 0, _maxX, 0, _maxAngCorrY);
	//end corr

	//calculo de angulos
	angCalcX = ReqAngle.AngleX - CurrentAngle.AngleX;
	angCalcY = (ReqAngle.AngleY + corrY) - CurrentAngle.AngleY;

	servoAngX = map(angCalcX, _minX, _maxX, _minServoXDif, _maxServoXDif);
	servoAngY = map(angCalcY, _minY, _maxY, _maxServoAl, _minServoAl);
	servoAng = servoAngX + servoAngY;

	if (servoAng > _maxServoAl)servoAng = _maxServoAl;
	if (servoAng < _minServoAl)servoAng = _minServoAl;
	//ajuste por velocidad
	//servoAng = ReqAngle.ESC > 1500 ? ((map(ReqAngle.ESC, 1400, 2000, 100, 70 ) * servoAng)/100) : servoAng;
	return servoAng;
}
int Autopilot::getServoPositionAlLft(Angle ReqAngle, Angle CurrentAngle)
{
	int angCalcX, angCalcY, servoAng, servoAngX, servoAngY;
	//correccion por giro
	int corrY = map(fabs(ReqAngle.AngleX), 0, _maxX, 0, _maxAngCorrY);
	//end corr

	//calculo de angulos
	angCalcX = ReqAngle.AngleX - CurrentAngle.AngleX;
	angCalcY = (ReqAngle.AngleY + corrY) - CurrentAngle.AngleY;

	servoAngX = map(angCalcX, _minX, _maxX, _minServoXDif, _maxServoXDif);
	servoAngY = map(angCalcY, _minY, _maxY, _minServoAl, _maxServoAl);
	servoAng = servoAngX + servoAngY;

	if (servoAng > _maxServoAl)servoAng = _maxServoAl;
	if (servoAng < _minServoAl)servoAng = _minServoAl;
	//ajuste por velocidad
	//servoAng = ReqAngle.ESC > 1500 ? ((map(ReqAngle.ESC, 1400, 2000, 100, 130) * servoAng) / 100) : servoAng;
	return servoAng;
}
//Manual servo position
int Autopilot::getManualServoPositionAlRgt(Angle ReqAngle)
{
	int angCalcX, angCalcY, servoAng, servoAngX, servoAngY;
	angCalcY = ReqAngle.AngleY;
	angCalcX = ReqAngle.AngleX;

	servoAngX = map(angCalcX, _minX, _maxX, _minServoXDif, _maxServoXDif);
	servoAngY = map(angCalcY, _minY, _maxY, _maxServoAl, _minServoAl);
	servoAng = servoAngX + servoAngY;

	if (servoAng > _maxServoAl)servoAng = _maxServoAl;
	if (servoAng < _minServoAl)servoAng = _minServoAl;
	return servoAng;
}
int Autopilot::getManualServoPositionAlLft(Angle ReqAngle)
{
	int angCalcX, angCalcY, servoAng, servoAngX, servoAngY;
	angCalcX = ReqAngle.AngleX;
	angCalcY = ReqAngle.AngleY;

	servoAngX = map(angCalcX, _minX, _maxX, _minServoXDif, _maxServoXDif);
	servoAngY = map(angCalcY, _minY, _maxY, _minServoAl, _maxServoAl);
	servoAng = servoAngX + servoAngY;

	if (servoAng > _maxServoAl)servoAng = _maxServoAl;
	if (servoAng < _minServoAl)servoAng = _minServoAl;
	return servoAng;
}
//checking angs & writing position
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
			servoESC.writeMicroseconds(position);
		}
	}

}
