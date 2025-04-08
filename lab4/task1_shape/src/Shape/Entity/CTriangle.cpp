#include "./CTriangle.h"
#include "../Exception/InvalidTriangleException.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, u_int32_t outlineColor, u_int32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	ValidateTriangle();
}

// formula: (1/2) |x 1 (y 2 − y 3 ) + x 2 (y 3 − y 1 ) + x 3 (y 1 − y 2 )|
double CTriangle::GetArea() const
{
	return abs(m_vertex1.x * (m_vertex2.y - m_vertex3.y) + m_vertex2.x * (m_vertex3.y - m_vertex1.y) + m_vertex3.x * (m_vertex1.y - m_vertex2.y)) / 2;
}

double CTriangle::GetPerimeter() const
{
	return GetLength(m_vertex1, m_vertex2) + GetLength(m_vertex2, m_vertex3) + GetLength(m_vertex3, m_vertex1);
}

std::string CTriangle::ToString(std::optional<int> precision) const
{
	std::ostringstream oss;
	if (precision.has_value())
	{
		oss << std::fixed << std::setprecision(precision.value());
	}
	oss << "vertex1: " << PointToString(GetVertex1(), precision)
		<< " vertex2: " << PointToString(GetVertex2(), precision)
		<< " vertex3: " << PointToString(GetVertex3(), precision)
		<< " type: triangle";

	return oss.str();
}

u_int32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

u_int32_t CTriangle::GetFillColor() const
{
	return m_outlineColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::ValidateTriangle()
{
	if (GetArea() == 0)
	{
		throw InvalidTriangleException();
	}
}