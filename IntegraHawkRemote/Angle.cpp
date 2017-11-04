// 
// 
// 

#include "Angle.h"
Angle::Angle(int x, int y)
{
	AngleX = x;
	AngleY = y;
}
String Angle::toString()
{
	return "AngX: " + String(AngleX) + " - AngY: " + String(AngleY);
}

