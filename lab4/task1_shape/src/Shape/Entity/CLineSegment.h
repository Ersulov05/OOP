#pragma once
#include "./CPoint.h"
#include "./IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, u_int32_t outlineColor = 0)
		: m_startPoint(startPoint)
		, m_endPoint(endPoint)
		, m_outlineColor(outlineColor)
	{
	}

	double GetArea() const override
	{
		return 0;
	}

	double GetPerimeter() const override
	{
		return GetLength(m_startPoint, m_endPoint);
	}

	std::string ToString() const override
	{
		return "line";
	}

	u_int32_t GetOutlineColor() const override
	{
		return m_outlineColor;
	}

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	u_int32_t m_outlineColor;
};