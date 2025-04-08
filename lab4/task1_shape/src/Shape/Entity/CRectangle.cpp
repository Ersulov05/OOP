#include "./CRectangle.h"
#include "../Exception/InvalidRectangleSizeException.h"

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom, u_int32_t outlineColor, u_int32_t fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	ValidateRectangle();
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
	return (GetWidth() + GetHeight()) * 2;
}

std::string CRectangle::ToString(std::optional<int> precision) const
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

u_int32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

u_int32_t CRectangle::GetFillColor() const
{
	return m_outlineColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return abs(m_rightBottom.x - m_leftTop.x);
}

double CRectangle::GetHeight() const
{
	return abs(m_leftTop.y - m_rightBottom.y);
}

void CRectangle::ValidateRectangle()
{
	if (GetWidth() <= 0 || GetHeight() <= 0)
	{
		throw InvalidRectangleSizeException();
	}
}