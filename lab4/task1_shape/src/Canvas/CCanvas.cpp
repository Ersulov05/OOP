#include "./CCanvas.h"
#include <iostream>

CCanvas::CCanvas(u_int32_t width, u_int32_t height)
	: m_window(sf::RenderWindow(sf::VideoMode(width, height), "Canvas"))
{
}
void CCanvas::DrawLine(CPoint from, CPoint to, u_int32_t lineColor)
{
	sf::Vertex line[] = {
		sf::Vertex(
			sf::Vector2f(from.x, from.y),
			ConvertColor(lineColor)),
		sf::Vertex(
			sf::Vector2f(to.x, to.y),
			ConvertColor(lineColor))
	};

	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, u_int32_t fillColor)
{
	if (points.size() < 3)
		return;

	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	polygon.setFillColor(ConvertColor(fillColor));

	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
	}

	m_window.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, u_int32_t lineColor)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center.x - radius, center.y - radius);
	circle.setOutlineColor(ConvertColor(lineColor));
	circle.setOutlineThickness(1.f);
	circle.setFillColor(sf::Color::Transparent);

	m_window.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, u_int32_t fillColor)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center.x - radius, center.y - radius);
	circle.setFillColor(ConvertColor(fillColor));
	circle.setOutlineThickness(0.f);

	m_window.draw(circle);
}

sf::Color CCanvas::ConvertColor(u_int32_t color) const
{
	return sf::Color(
		(color >> 16) & 0xFF, // R
		(color >> 8) & 0xFF, // G
		color & 0xFF, // B
		(color >> 24) & 0xFF // A
	);
}

void CCanvas::Display()
{
	m_window.display();
}

void CCanvas::Clear(u_int32_t color)
{
	m_window.clear(sf::Color(color));
}

bool CCanvas::IsOpen() const
{
	return m_window.isOpen();
}

void CCanvas::ProcessEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}