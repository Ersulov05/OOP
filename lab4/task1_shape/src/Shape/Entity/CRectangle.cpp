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
	return m_rightBottom.x - m_leftTop.x;
}

double CRectangle::GetHeight() const
{
	return m_rightBottom.y - m_leftTop.y;
}

void CRectangle::ValidateRectangle()
{
	if (GetWidth() <= 0 || GetHeight() <= 0)
	{
		throw InvalidRectangleSizeException();
	}
}

void CRectangle::Draw(ICanvas& canvas)
{
	CPoint rightTop(m_rightBottom.x, m_leftTop.y);
	CPoint leftBottom(m_leftTop.x, m_rightBottom.y);
	std::vector<CPoint> points = {
		m_leftTop, rightTop, m_rightBottom, leftBottom
	};
	canvas.FillPolygon(points, m_fillColor);
	canvas.DrawLine(m_leftTop, rightTop, m_outlineColor);
	canvas.DrawLine(rightTop, m_rightBottom, m_outlineColor);
	canvas.DrawLine(m_rightBottom, leftBottom, m_outlineColor);
	canvas.DrawLine(leftBottom, m_leftTop, m_outlineColor);
}