#pragma once
#include "../Entity/IShape.h"
#include <vector>

class ShapeRepository
{
public:
	~ShapeRepository();
	void StoreShape(IShape* shape);
	const std::vector<IShape*> GetAllShapes() const;
	const IShape* GetShapeWithMaxArea() const;
	const IShape* GetShapeWithMinPerimeter() const;

private:
	std::vector<IShape*> m_shapes;
};