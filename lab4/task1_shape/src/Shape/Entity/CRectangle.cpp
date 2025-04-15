#include "./CRectangle.h"
#include "../Exception/InvalidRectangleSizeException.h"

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom, u_int32_t outlineColor, u_int32_t fillColor)
	: ISolidShape::ISolidShape(outlineColor, fillColor)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
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
	if (precision)
	{
		oss << std::fixed << std::setprecision(*precision);
	}
	oss << "Type: rectangle"
		<< " LeftTopPoint: " << PointToString(m_leftTop, precision)
		<< " RightBottom: " << PointToString(m_rightBottom, precision)
		<< " Width: " << std::to_string(GetWidth())
		<< " Height: " << std::to_string(GetHeight())
		<< " " << ISolidShape::ToString(precision);
	return oss.str();
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