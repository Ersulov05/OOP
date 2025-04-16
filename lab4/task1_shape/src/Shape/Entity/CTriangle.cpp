#include "./CTriangle.h"
#include "../Exception/InvalidTriangleException.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, u_int32_t outlineColor, u_int32_t fillColor)
	: ISolidShape::ISolidShape(outlineColor, fillColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
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
	if (precision)
	{
		oss << std::fixed << std::setprecision(*precision);
	}
	oss << "Type: triangle"
		<< " Vertex1: " << PointToString(GetVertex1(), precision)
		<< " Vertex2: " << PointToString(GetVertex2(), precision)
		<< " Vertex3: " << PointToString(GetVertex3(), precision)
		<< " " << ISolidShape::ToString(precision);
	return oss.str();
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
		// throw InvalidTriangleException();
	}
}

void CTriangle::Draw(ICanvas& canvas)
{
	std::vector<CPoint> points = {
		m_vertex1, m_vertex2, m_vertex3
	};
	canvas.FillPolygon(points, m_fillColor);
	canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);
}