#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../../../catch/catch.hpp"
#include "../../../src/Shape/Entity/CCircle.h"
#include "../../../src/Shape/Exception/InvalidCircleRadiusException.h"

bool DoubleEquals(double a, double b)
{
	const double epsilon = 1e-10;
	return std::fabs(a - a) < epsilon;
}

TEST_CASE("TestCreateCircle")
{
	double radius = 10;
	CPoint center(0, 0);
	CCircle circle = CCircle(CPoint(0, 0), 10);

	REQUIRE(DoubleEquals(circle.GetArea(), M_PI * radius * radius));
	REQUIRE(circle.GetCenter() == center);
	REQUIRE(DoubleEquals(circle.GetPerimeter(), M_PI * radius * 2));
	REQUIRE(DoubleEquals(circle.GetRadius(), radius));

	REQUIRE_THROWS_AS(CCircle(CPoint(0, 0), 0), InvalidCircleRadiusException);
	REQUIRE_THROWS_AS(CCircle(CPoint(0, 0), -1), InvalidCircleRadiusException);
}