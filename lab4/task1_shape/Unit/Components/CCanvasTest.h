#pragma once
#include "../../src/Canvas/ICanvas.h"
#include "../../src/Shape/Entity/CPoint.h"
#include <vector>

class CCanvasTest : public ICanvas
{
public:
	CCanvasTest(std::ostream& output);
	void DrawLine(CPoint from, CPoint to, u_int32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, u_int32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, u_int32_t lineColor) override;
	void FillCircle(CPoint center, double radius, u_int32_t fillColor) override;

private:
	std::ostream& m_output;
};