#pragma once
#include "./CPoint.h"
#include "./IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, u_int32_t outlineColor = 0);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString(std::optional<int> precision = std::nullopt) const override;
	u_int32_t GetOutlineColor() const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	u_int32_t m_outlineColor;
};