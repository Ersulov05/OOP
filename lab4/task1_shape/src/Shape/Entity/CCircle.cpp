#include "./CCircle.h"
#include "../Exception/InvalidCircleRadiusException.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CCircle::CCircle(CPoint center, double radius, u_int32_t outlineColor, u_int32_t fillColor)
	: ISolidShape::ISolidShape(outlineColor, fillColor)
	, m_center(center)
	, m_radius(radius)
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

void CCircle::Draw(ICanvas& canvas)
{
	canvas.FillCircle(m_center, m_radius, m_fillColor);
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
}

std::string CCircle::ToString(std::optional<int> precision) const
{
	std::ostringstream oss;
	if (precision)
	{
		oss << std::fixed << std::setprecision(*precision);
	}
	oss << "Type: circle"
		<< " Center: " << PointToString(GetCenter(), precision)
		<< " Radius: " << m_radius
		<< " " << ISolidShape::ToString(precision);
	return oss.str();
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