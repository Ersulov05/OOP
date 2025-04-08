#include "./CCircle.h"
#include "../Exception/InvalidCircleRadiusException.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CCircle::CCircle(CPoint center, double radius, u_int32_t outlineColor, u_int32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	ValidateCircle();
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return M_PI * m_radius * 2;
}

std::string CCircle::ToString(std::optional<int> precision) const
{
	std::ostringstream oss;
	if (precision.has_value())
	{
		oss << std::fixed << std::setprecision(precision.value());
	}
	oss << "center: " << PointToString(GetCenter(), precision)
		<< " radius: " << GetRadius()
		<< " type: circle";

	return oss.str();
}

u_int32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

u_int32_t CCircle::GetFillColor() const
{
	return m_outlineColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::ValidateCircle()
{
	if (m_radius <= 0)
	{
		throw InvalidCircleRadiusException();
	}
}