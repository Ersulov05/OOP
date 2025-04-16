#define CATCH_CONFIG_MAIN
#include "../../../../../catch/catch.hpp"
#include "../../../src/Shape/Entity/CCircle.h"
#include "../../../src/Shape/Entity/CRectangle.h"
#include "../../../src/Shape/Repository/ShapeRepository.h"

TEST_CASE("TestShapeRepository")
{
	ShapeRepository shapeRepository;
	auto shape = shapeRepository.GetShapeWithMaxArea();
	REQUIRE(shape == nullptr);

	shape = shapeRepository.GetShapeWithMinPerimeter();
	REQUIRE(shape == nullptr);

	CCircle* circle = new CCircle(CPoint(0, 0), 10);
	shapeRepository.StoreShape(circle);

	auto shapes = shapeRepository.GetAllShapes();

	REQUIRE(shapes.size() == 1);

	shape = shapeRepository.GetShapeWithMaxArea();
	REQUIRE(shape->GetArea() == circle->GetArea());
	REQUIRE(shape->GetPerimeter() == circle->GetPerimeter());

	shape = shapeRepository.GetShapeWithMinPerimeter();
	REQUIRE(shape->GetArea() == circle->GetArea());
	REQUIRE(shape->GetPerimeter() == circle->GetPerimeter());

	CRectangle* rectangle = new CRectangle(CPoint(0, 0), CPoint(10, 10), 0xff00ff00, 0xffffffff);
	shapeRepository.StoreShape(rectangle);

	shapes = shapeRepository.GetAllShapes();
	REQUIRE(shapes.size() == 2);

	shape = shapeRepository.GetShapeWithMaxArea();
	REQUIRE(shape->GetArea() == circle->GetArea());
	REQUIRE(shape->GetPerimeter() == circle->GetPerimeter());

	shape = shapeRepository.GetShapeWithMinPerimeter();
	REQUIRE(shape->GetArea() == rectangle->GetArea());
	REQUIRE(shape->GetPerimeter() == rectangle->GetPerimeter());
}