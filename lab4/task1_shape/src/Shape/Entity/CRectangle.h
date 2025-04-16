#pragma once
#include "./CPoint.h"
#include "./ISolidShape.h"

class CRectangle : public ISolidShape
{
public:
	CRectangle(CPoint leftTop, CPoint rightBottom, u_int32_t outlineColor = 0xffffffff, u_int32_t fillColor = 0xffffffff);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString(std::optional<int> precision = std::nullopt) const override;
	void Draw(ICanvas& canvas) override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	void ValidateRectangle();

	CPoint m_leftTop;
	CPoint m_rightBottom;
};