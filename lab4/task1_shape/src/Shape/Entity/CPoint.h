#pragma once
#include <cmath>

struct CPoint
{
	double x;
	double y;

	CPoint(double x, double y)
		: x(x)
		, y(y)
	{
	}
};

double GetLength(CPoint startPoint, CPoint endPoint)
{
	double dx = endPoint.x - startPoint.x;
	double dy = endPoint.y - startPoint.x;

	return sqrt(dx * dx + dy * dy);
}