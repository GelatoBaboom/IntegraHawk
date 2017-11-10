// 
// 
// 

#include "Angle.h"
Angle::Angle(double x, double y, double z)
{
	AngleX = x;
	AngleY = y;
	AngleZ = z;
	HasAngle = true;
}
Angle::Angle(double x, double y, double z, bool hasAngle)
{
	AngleX = x;
	AngleY = y;
	AngleZ = z;
	HasAngle = hasAngle;
}
Angle::Angle(String xy)
{
	//AngleX = 
	String Xval;
	String Yval;
	String key;
	for (char & c : xy)
	{
		if (key == "X:")
		{
			if (c != ';') { Xval += c; }
			else { key = ""; }
		}
		else if (key == "Y:")
		{
			if (c != ';') { Yval += c; }
			else { key = ""; }
		}
		else { key += c; }
		c = '*';
	}
	if (Xval.length() > 0 && Yval.length() > 0) {
		AngleX = Xval.toDouble();
		AngleY = Yval.toDouble();
		AngleZ = 0.0;
		HasAngle = true;
	}
	else
	{
		AngleX = 0.0;
		AngleY = 0.0;
		AngleZ = 0.0;
		HasAngle = false;
	}
}
String Angle::toString()
{
	return "X:" + String(AngleX) + ";Y:" + String(AngleY) + ";Z:" + String(AngleZ) + ";";
}

