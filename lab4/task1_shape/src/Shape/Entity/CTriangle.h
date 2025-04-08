#pragma once
#include "./CPoint.h"
#include "./ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, u_int32_t outlineColor = 0, u_int32_t fillColor = 0);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString(std::optional<int> precision = std::nullopt) const override;
	u_int32_t GetOutlineColor() const override;
	u_int32_t GetFillColor() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	void ValidateTriangle();

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	u_int32_t m_outlineColor;
	u_int32_t m_fillColor;
};