#pragma once
#include "../Shape/Entity/CPoint.h"
#include "./ICanvas.h"
#include <SFML/Graphics.hpp>
#include <vector>

class CCanvas : public ICanvas
{
public:
	CCanvas(u_int32_t width, u_int32_t height);
	void DrawLine(CPoint from, CPoint to, u_int32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, u_int32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, u_int32_t lineColor) override;
	void FillCircle(CPoint center, double radius, u_int32_t fillColor) override;

	void Display();
	void Clear(u_int32_t color);
	bool IsOpen() const;
	void ProcessEvents();

private:
	sf::Color ConvertColor(u_int32_t color) const;
	sf::RenderWindow m_window;
};