#include "Autopilot.h"
#include <Servo.h>
Servo servoX;
Servo servoY;
Servo servoZ;
int CurrentPosX;
int CurrentPosY;
int CurrentPosZ;
Autopilot::Autopilot()
{

}
void Autopilot::init()
{
	servoX.attach(10);
	servoY.attach(11);
	servoZ.attach(9);
}
void Autopilot::Control(Angle ReqAngle, Angle CurrentAngle)
{
	int servoPosX, servoPosZ;
	//Giro y Compensacion guiñada
	servoPosX = getServoPositionX(ReqAngle.AngleX, CurrentAngle.AngleX);
	servoPosZ = getServoPositionZ(servoPosX);
	servoMove(servoPosX, 'X');
	servoMove(servoPosZ, 'Z');

	//y lo mismo va para Y pero con una correccion en el angulo 0
	//para que deje cabezar aerodinamicamente al plano
}
int Autopilot::getServoPositionX(double ReqAngle, double CurrentAngle)
{
	int position, servoAng;
	position = ReqAngle - CurrentAngle;
	//Serial.println("Pos: " + String(position) + " RA: " + String(ReqAngle) + " CA: " + String(CurrentAngle));
	servoAng = map(position, -45, 45, _minServoX, _maxServoX);
	if (servoAng > _maxServoX)servoAng = _maxServoX;
	if (servoAng < _minServoX)servoAng = _minServoX;
	return servoAng;
}
int Autopilot::getServoPositionZ(int PositionX)
{
	int position;
	position = PositionX * 0.3;
	return position;
}
void Autopilot::servoMove(int position, char ServoCoor)
{
	if (ServoCoor == 'X')
	{
		if (position != CurrentPosX) {
			CurrentPosX = position;
			servoX.write(position);
		}
	}
	if (ServoCoor == 'Y')
	{
		if (position != CurrentPosY) {
			CurrentPosY = position;
			servoY.write(position);
		}
	}
	if (ServoCoor == 'Z')
	{
		if (position != CurrentPosZ) {
			CurrentPosZ = position;
			servoZ.write(position);
		}
	}

}
