#pragma once
#include <optional>
#include <string>

class IShape
{
public:
	virtual ~IShape() = default;
	IShape(u_int32_t outlineColor = 0)
		: m_outlineColor(outlineColor){};
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;

	u_int32_t GetOutlineColor() const
	{
		return m_outlineColor;
	}

	virtual u_int32_t GetFillColor() const
	{
		return m_outlineColor;
	}

	virtual std::string ToString(std::optional<int> precision = std::nullopt) const
	{
		std::ostringstream oss;
		if (precision)
		{
			oss << std::fixed << std::setprecision(*precision);
		}
		oss << "Area: " << GetArea() << " Perimeter: " << GetPerimeter()
			<< " OutlineColor: " << std::hex << std::setw(6) << std::setfill('0')
			<< GetOutlineColor();
		return oss.str();
	}

private:
	u_int32_t m_outlineColor;
};