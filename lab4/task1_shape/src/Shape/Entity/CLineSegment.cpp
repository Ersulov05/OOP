#include "./CLineSegment.h"
#include "./CPoint.h"
#include "./IShape.h"
#include <optional>

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, u_int32_t outlineColor)
	: IShape::IShape(outlineColor)
	, m_startPoint(startPoint)
	, m_endPoint(endPoint)
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
	std::ostringstream oss;
	if (precision)
	{
		oss << std::fixed << std::setprecision(*precision);
	}
	oss << "Type: line"
		<< " StartPoint: " << PointToString(m_startPoint, precision)
		<< " EndPoint: " << PointToString(m_startPoint, precision)
		<< " " << IShape::ToString(precision);
	return oss.str();
}

void CLineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}