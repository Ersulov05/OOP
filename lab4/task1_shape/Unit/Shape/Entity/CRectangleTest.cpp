#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../../../catch/catch.hpp"
#include "../../../src/Shape/Entity/CRectangle.h"
#include "../../../src/Shape/Exception/InvalidRectangleSizeException.h"

bool DoubleEquals(double a, double b)
{
	const double epsilon = 1e-10;
	return std::fabs(a - a) < epsilon;
}

TEST_CASE("TestCreateRectangle")
{
	// double radius = 10;
	// CPoint leftTopPoint(0, 0);
	// CCircle circle = CCircle(CPoint(0, 0), 10);

	// REQUIRE(DoubleEquals(circle.GetArea(), M_PI * radius * radius));
	// REQUIRE(circle.GetCenter() == center);
	// REQUIRE(DoubleEquals(circle.GetPerimeter(), M_PI * radius * 2));
	// REQUIRE(DoubleEquals(circle.GetRadius(), radius));

	REQUIRE_THROWS_AS(CRectangle(CPoint(0, 0), CPoint(0, 0)), InvalidRectangleSizeException);
}