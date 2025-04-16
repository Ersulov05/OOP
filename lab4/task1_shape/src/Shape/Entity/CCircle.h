#pragma once
#include "./CPoint.h"
#include "./ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	CCircle(CPoint center, double radius, u_int32_t outlineColor = 0xffffffff, u_int32_t fillColor = 0xffffffff);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString(std::optional<int> precision = std::nullopt) const override;
	void Draw(ICanvas& canvas) override;
	CPoint GetCenter() const;
	double GetRadius() const;

private:
	void ValidateCircle();

	CPoint m_center;
	double m_radius;
};