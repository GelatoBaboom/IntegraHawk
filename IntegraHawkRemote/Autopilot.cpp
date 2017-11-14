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
	servoX.attach(9);
	servoY.attach(10);
	servoZ.attach(11);
}
void Autopilot::Control(Angle ReqAngle, Angle CurrentAngle)
{
	int servoPosX, servoPosY, servoPosZ;
	//Giro y Compensacion guiñada
	servoPosX = getServoPositionX(ReqAngle.AngleX, CurrentAngle.AngleX);
	servoPosZ = getServoPositionZ(servoPosX);
	servoMove(servoPosX, 'X');
	servoMove(servoPosZ, 'Z');
	//el strict mode debe ser modificable desde el control
	servoPosY = getServoPositionY(ReqAngle.AngleY, CurrentAngle.AngleY, true);
	//Serial.println("PosX: " + String(servoPosX) + " PosZ: " + String(servoPosZ) + " PosY: " + String(servoPosY));
	servoMove(servoPosY, 'Y');
}
int Autopilot::getServoPositionY(double ReqAngle, double CurrentAngle, bool StrictMode)
{
	int angCalc, servoAng;
	angCalc = ReqAngle - CurrentAngle;
	bool hasReqAngle = false;
	if (ReqAngle > 1 || ReqAngle < -1) { hasReqAngle = true; }
	if (StrictMode == true && hasReqAngle == false && CurrentAngle > -18 && CurrentAngle < 18) { angCalc = 0; }
	//if (StrictMode == true && hasReqAngle == false && angCalc > 1) { angCalc = angCalc - 18; }
	//if (StrictMode == true && hasReqAngle == false && angCalc < -1) { angCalc = angCalc + 18; }
	servoAng = map(angCalc, -45, 45, _minServoY, _maxServoY);
	if (servoAng > _maxServoY)servoAng = _maxServoY;
	if (servoAng < _minServoY)servoAng = _minServoY;
	return servoAng;
}
int Autopilot::getServoPositionX(double ReqAngle, double CurrentAngle)
{
	int angCalc, servoAng;
	angCalc = ReqAngle -CurrentAngle;
	servoAng = map(angCalc, -45, 45, _minServoX, _maxServoX);
	if (servoAng > _maxServoX)servoAng = _maxServoX;
	if (servoAng < _minServoX)servoAng = _minServoX;
	return servoAng;
}
int Autopilot::getServoPositionZ(int PositionX)
{
	int position;
	position = map(PositionX, _minServoX, _maxServoX, _minServoZ, _maxServoZ);
	return position;
}
void Autopilot::servoMove(int position, char ServoCoor)
{
	if (ServoCoor == 'X')
	{
		if (position != CurrentPosX) {
			//Serial.println("Pos: " + String(CurrentPosX));
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
