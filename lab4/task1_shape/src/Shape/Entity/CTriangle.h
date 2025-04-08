#pragma once
#include "../Exception/InvalidTriangleException.h"
#include "./CPoint.h"
#include "./ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, u_int32_t outlineColor = 0, u_int32_t fillColor = 0)
		: m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
		ValidateTriangle();
	}

	// formula: (1/2) |x 1 (y 2 − y 3 ) + x 2 (y 3 − y 1 ) + x 3 (y 1 − y 2 )|
	double GetArea() const override
	{
		return abs(m_vertex1.x * (m_vertex2.y - m_vertex3.y) + m_vertex2.x * (m_vertex3.y - m_vertex1.y) + m_vertex3.x * (m_vertex1.y - m_vertex2.y)) / 2;
	}

	double GetPerimeter() const override
	{
		return GetLength(m_vertex1, m_vertex2) + GetLength(m_vertex2, m_vertex3) + GetLength(m_vertex3, m_vertex1);
	}

	std::string ToString(std::optional<int> precision = std::nullopt) const override
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

	u_int32_t GetOutlineColor() const override
	{
		return m_outlineColor;
	}

	u_int32_t GetFillColor() const override
	{
		return m_outlineColor;
	}

	CPoint GetVertex1() const
	{
		return m_vertex1;
	}

	CPoint GetVertex2() const
	{
		return m_vertex2;
	}

	CPoint GetVertex3() const
	{
		return m_vertex3;
	}

private:
	void ValidateTriangle()
	{
		if (GetArea() == 0)
		{
			throw InvalidTriangleException();
		}
	}
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	u_int32_t m_outlineColor;
	u_int32_t m_fillColor;
};