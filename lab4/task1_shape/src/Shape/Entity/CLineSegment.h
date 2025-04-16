#pragma once
#include "./CPoint.h"
#include "./IShape.h"
#include <optional>

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, u_int32_t outlineColor = 0xffffffff);
	double GetArea() const override;
	double GetPerimeter() const override;
	void Draw(ICanvas& canvas) override;
	std::string ToString(std::optional<int> precision = std::nullopt) const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};