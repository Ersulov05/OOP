#pragma once
#include <optional>
#include <string>

class IShape
{
public:
	virtual ~IShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString(std::optional<int> precision = std::nullopt) const = 0;
	virtual u_int32_t GetOutlineColor() const = 0;
};