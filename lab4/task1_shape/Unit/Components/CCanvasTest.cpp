#include "./CCanvasTest.h"

CCanvasTest::CCanvasTest(std::ostream& output)
	: m_output(output)
{
}

void CCanvasTest::DrawLine(CPoint from, CPoint to, u_int32_t lineColor)
{
	m_output << "line is drawn from " << PointToString(from) << " to " << PointToString(to) << std::endl;
}

void CCanvasTest::FillPolygon(std::vector<CPoint> points, u_int32_t fillColor)
{
	m_output << "the polygon is filled in by points";
	for (const auto& point : points)
	{
		m_output << " " << PointToString(point);
	}
	m_output << std::endl;
}

void CCanvasTest::DrawCircle(CPoint center, double radius, u_int32_t lineColor)
{
	m_output << "circle has been drawn with the center at " << PointToString(center) << " and the radius " << radius << std::endl;
}

void CCanvasTest::FillCircle(CPoint center, double radius, u_int32_t fillColor)
{
	m_output << "circle centered in is filled in " << PointToString(center) << " and the radius " << radius << std::endl;
}