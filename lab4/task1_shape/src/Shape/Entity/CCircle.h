#pragma once
#include "./CPoint.h"
#include "./ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius, u_int32_t outlineColor = 0, u_int32_t fillColor = 0);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString(std::optional<int> precision = std::nullopt) const override;
	u_int32_t GetOutlineColor() const override;
	u_int32_t GetFillColor() const override;
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	void ValidateCircle();

	CPoint m_center;
	double m_radius;
	u_int32_t m_outlineColor;
	u_int32_t m_fillColor;
};