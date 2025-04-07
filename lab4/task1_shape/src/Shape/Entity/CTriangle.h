#pragma once
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

	double GetArea() const override
	{
		return 0;
	}

	double GetPerimeter() const override
	{
		return GetLength(m_vertex1, m_vertex2) + GetLength(m_vertex2, m_vertex3) + GetLength(m_vertex3, m_vertex1);
	}

	std::string ToString() const override
	{
		return "triangle";
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
	}
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	u_int32_t m_outlineColor;
	u_int32_t m_fillColor;
};