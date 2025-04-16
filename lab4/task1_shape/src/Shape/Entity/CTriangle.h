#pragma once
#include "./CPoint.h"
#include "./ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, u_int32_t outlineColor = 0xffffffff, u_int32_t fillColor = 0xffffffff);
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString(std::optional<int> precision = std::nullopt) const override;
	void Draw(ICanvas& canvas) override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	void ValidateTriangle();

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
};