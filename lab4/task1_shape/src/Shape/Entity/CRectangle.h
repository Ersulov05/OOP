#pragma once
#include "../Exception/InvalidRectangleSizeException.h"
#include "./CPoint.h"
#include "./ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, CPoint rightBottom, u_int32_t outlineColor = 0, u_int32_t fillColor = 0)
		: m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
		ValidateRectangle();
	}

	double GetArea() const override
	{
		return GetWidth() * GetHeight();
	}

	double GetPerimeter() const override
	{
		return (GetWidth() + GetHeight()) * 2;
	}

	std::string ToString(std::optional<int> precision = std::nullopt) const override
	{
		std::ostringstream oss;
		if (precision.has_value())
		{
			oss << std::fixed << std::setprecision(precision.value());
		}
		oss << "leftTopPoint: " << PointToString(m_leftTop, precision)
			<< " rightBottom: " << PointToString(m_rightBottom, precision)
			<< " width: " << std::to_string(GetWidth())
			<< " height: " << std::to_string(GetHeight())
			<< " type: rectangle";

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

	CPoint GetLeftTop() const
	{
		return m_leftTop;
	}

	CPoint GetRightBottom() const
	{
		return m_rightBottom;
	}

	double GetWidth() const
	{
		return abs(m_rightBottom.x - m_leftTop.x);
	}

	double GetHeight() const
	{
		return abs(m_leftTop.y - m_rightBottom.y);
	}

private:
	void ValidateRectangle()
	{
		if (GetWidth() <= 0 || GetHeight() <= 0)
		{
			throw InvalidRectangleSizeException();
		}
	}
	CPoint m_leftTop;
	CPoint m_rightBottom;
	u_int32_t m_outlineColor;
	u_int32_t m_fillColor;
};