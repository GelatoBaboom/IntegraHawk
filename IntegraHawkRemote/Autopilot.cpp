// 
// 
// 

#include "Autopilot.h"
#include <Servo.h>
Servo servoX;
Servo servoY;
Autopilot::Autopilot()
{
	servoX.attach(10);
	servoY.attach(11);
}
void Autopilot::Control(Angle ReqAngle, Angle CurrentAngle)
{
	int servoPosX;
	servoPosX = getServoPosition(ReqAngle.AngleX, CurrentAngle.AngleX);
	servoMove(servoPosX, 'X');
	//y lo mismo va para Y pero con una correccion en el angulo 0
	//para que deje cabezar aerodinamicamente al plano
}
int Autopilot::getServoPosition(double ReqAngle, double CurrentAngle)
{
	int position, servoAng;
	position = ReqAngle - CurrentAngle;
	servoAng = map(position, -60, 60, 0, 180);
	return servoAng;
}
void Autopilot::servoMove(int position, char ServoCoor)
{
	if (ServoCoor == 'X')
	{
		servoX.write(position);
	}
	if (ServoCoor == 'Y')
	{
		servoY.write(position);
	}

}
