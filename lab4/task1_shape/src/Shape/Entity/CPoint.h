#pragma once
#include <cmath>
#include <iomanip>
#include <optional>

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

double GetLength(const CPoint& startPoint, const CPoint& endPoint)
{
	double dx = endPoint.x - startPoint.x;
	double dy = endPoint.y - startPoint.y;

	return sqrt(dx * dx + dy * dy);
}

std::string PointToString(const CPoint& point, std::optional<int> precision = std::nullopt)
{
	std::ostringstream oss;
	if (precision.has_value())
	{
		oss << std::fixed << std::setprecision(precision.value());
	}

	oss << "(" << point.x << ", " << point.y << ")";
	return oss.str();
}