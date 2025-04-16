#pragma once
#include "./IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() = default;
	ISolidShape(u_int32_t outlineColor = 0xffffffff, u_int32_t fillColor = 0xffffffff)
		: IShape::IShape(outlineColor)
		, m_fillColor(fillColor){};

	u_int32_t GetFillColor() const override
	{
		return m_fillColor;
	}

	std::string ToString(std::optional<int> precision = std::nullopt) const override
	{
		std::ostringstream oss;
		oss << IShape::ToString(precision)
			<< " FillColor: " << std::hex << std::setw(8) << std::setfill('0')
			<< GetFillColor();
		return oss.str();
	}

protected:
	u_int32_t m_fillColor;
};