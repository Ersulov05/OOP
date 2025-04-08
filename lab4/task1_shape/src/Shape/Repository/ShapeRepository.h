#pragma once
#include "../Entity/IShape.h"
#include <memory>
#include <vector>

class ShapeRepository
{
public:
	~ShapeRepository()
	{
		m_shapes.clear();
	}

	void StoreShape(IShape* shape)
	{
		m_shapes.push_back(shape);
	}

	const std::vector<IShape*> GetAllShapes() const
	{
		return m_shapes;
	}

	const IShape* GetShapeWithMaxArea() const
	{
		IShape* shapeWithMaxArea = nullptr;
		for (const auto& shape : m_shapes)
		{
			if (!shapeWithMaxArea || shape->GetArea() > shapeWithMaxArea->GetArea())
			{
				shapeWithMaxArea = shape;
			}
		}

		return shapeWithMaxArea;
	}

	const IShape* GetShapeWithMinPerimeter() const
	{
		IShape* shapeWithMinPerimeter = nullptr;
		for (const auto& shape : m_shapes)
		{
			if (!shapeWithMinPerimeter || shape->GetPerimeter() < shapeWithMinPerimeter->GetPerimeter())
			{
				shapeWithMinPerimeter = shape;
			}
		}

		return shapeWithMinPerimeter;
	}

private:
	std::vector<IShape*> m_shapes;
};