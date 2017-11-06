// 
// 
// 

#include "Angle.h"
Angle::Angle(double x, double y)
{
	AngleX = x;
	AngleY = y;
}
Angle::Angle(double x, double y, bool hasAngle)
{
  AngleX = x;
  AngleY = y;
  HasAngle = hasAngle;
}
Angle::Angle(String xy)
{
	//AngleX = 
}
String Angle::toString()
{
	return "AngX: " + String(AngleX) + " - AngY: " + String(AngleY);
}

