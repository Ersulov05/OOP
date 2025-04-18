#include "./ShapeRepository.h"
#include <vector>

ShapeRepository::~ShapeRepository()
{
	m_shapes.clear(); // Очистка памяти
}

void ShapeRepository::StoreShape(IShape* shape)
{
	m_shapes.push_back(shape);
}

const std::vector<IShape*> ShapeRepository::GetAllShapes() const
{
	return m_shapes;
}

const IShape* ShapeRepository::GetShapeWithMaxArea() const
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

const IShape* ShapeRepository::GetShapeWithMinPerimeter() const
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