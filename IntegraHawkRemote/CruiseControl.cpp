// 
// 
// 

#include "CruiseControl.h"
double lastCourseZ = 0.0;
double correctionCourseY = 0.0;
CruiseControl::CruiseControl() {

}
double CruiseControl::getCourse(Angle current, double turn)
{
	lastCourseZ = (turn < 0) ? current.AngleZ + 10.0 : current.AngleZ - 10.0;
	double retCourse = (lastCourseZ > 0) ? current.AngleZ - turn : current.AngleZ + turn;
}


Angle CruiseControl::getAnglesFromCourse(Angle current, double retCourse)
{
	Angle aCurse(0, 0, 0, false);
	double diff = retCourse - current.AngleZ;
	double x = 15.0;
	double y = 12.0;
	bool endRet = false;
	if (diff < 10 && diff > -10)
	{
		x = 0.0;
		y = 0.0;
		endRet = true;
	}
	if (endRet)
	{
		if (((micros() - cruiserTimer) / 1000) > 500)
		{
			cruiserTimer = micros();
			double courseY = y + current.AngleY;
			correctionCourseY = ((courseY< 0.5 && courseY> -0.5) ? correctionCourseY : (courseY < 0.0) ? correctionCourseY + 1.0 : correctionCourseY - 1.0);
		}
		y = y + correctionCourseY;
	}
	if (lastCourseZ > 0)
	{
		if (current.AngleZ < lastCourseZ && current.AngleZ>retCourse) {
			aCurse = Angle(x, y, 0.0);
		}
		else
		{
			aCurse = Angle(-x, y, 0.0);
		}
	}
	else
	{
		if (current.AngleZ > lastCourseZ && current.AngleZ < retCourse) {
			aCurse = Angle(-x, y, 0.0);
		}
		else
		{
			aCurse = Angle(x, y, 0.0);
		}
	}
	aCurse.ESC = 1400;
}
