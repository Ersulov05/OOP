#pragma once
#include "../Shape/Entity/CPoint.h"
#include "./ICanvas.h"
#include <vector>

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual void DrawLine(CPoint from, CPoint to, u_int32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> points, u_int32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, u_int32_t lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, u_int32_t fillColor) = 0;
};