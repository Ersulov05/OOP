#include "./CLineSegment.h"
#include "./CPoint.h"
#include "./IShape.h"
#include <optional>

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, u_int32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return GetLength(m_startPoint, m_endPoint);
}

std::string CLineSegment::ToString(std::optional<int> precision) const
{
	return "type: line";
}

u_int32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}