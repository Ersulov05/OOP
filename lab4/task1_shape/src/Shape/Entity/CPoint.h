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

	bool operator==(const CPoint& other) const
	{
		const double epsilon = 1e-10;
		return std::fabs(x - other.x) < epsilon
			&& std::fabs(y - other.y) < epsilon;
	}
};

inline double GetLength(const CPoint& startPoint, const CPoint& endPoint)
{
	double dx = endPoint.x - startPoint.x;
	double dy = endPoint.y - startPoint.y;

	return sqrt(dx * dx + dy * dy);
}

inline std::string PointToString(const CPoint& point, std::optional<int> precision = std::nullopt)
{
	std::ostringstream oss;
	if (precision.has_value())
	{
		oss << std::fixed << std::setprecision(precision.value());
	}

	oss << "(" << point.x << ", " << point.y << ")";
	return oss.str();
}