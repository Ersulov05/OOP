#pragma once
#include "./IShape.h"

class ISolidShape : public IShape
{
public:
	virtual ~ISolidShape() = default;
	virtual u_int32_t GetFillColor() const = 0;
};