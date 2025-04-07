#pragma once
#include "./CPoint.h"
#include "./ISolidShape.h"
#include <cmath>

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius, u_int32_t outlineColor = 0, u_int32_t fillColor = 0)
		: m_center(center)
		, m_radius(radius)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
		ValidateCircle();
	}

	double GetArea() const override
	{
		return M_PI * m_radius * m_radius;
	}

	double GetPerimeter() const override
	{
		return M_PI * m_radius * 2;
	}

	std::string ToString() const override
	{
		return "circle";
	}

	u_int32_t GetOutlineColor() const override
	{
		return m_outlineColor;
	}

	u_int32_t GetFillColor() const override
	{
		return m_outlineColor;
	}

	CPoint GetCenter() const
	{
		return m_center;
	}

	double GetRadius() const
	{
		return m_radius;
	}

private:
	void ValidateCircle()
	{
	}
	CPoint m_center;
	double m_radius;
	u_int32_t m_outlineColor;
	u_int32_t m_fillColor;
};