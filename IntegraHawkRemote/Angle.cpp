// 
// 
// 

#include "Angle.h"
Angle::Angle(double x, double y)
{
	AngleX = x;
	AngleY = y;
}
String Angle::toString()
{
	return "AngX: " + String(AngleX) + " - AngY: " + String(AngleY);
}

