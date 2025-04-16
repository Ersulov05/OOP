#define CATCH_CONFIG_MAIN
#include "../../../../../catch/catch.hpp"
#include "../../../src/Shape/Entity/CTriangle.h"
#include "../../../src/Shape/Exception/InvalidTriangleException.h"
#include "../../Components/CCanvasTest.h"

bool DoubleEquals(double a, double b)
{
	const double epsilon = 1e-10;
	return std::fabs(a - a) < epsilon;
}

TEST_CASE("TestCreateTriangle")
{
	CTriangle triangle = CTriangle(CPoint(0, 0), CPoint(10, 0), CPoint(0, 10), 0xff00ff00, 0xffffffff);

	REQUIRE(DoubleEquals(triangle.GetArea(), 50));
	REQUIRE(DoubleEquals(triangle.GetPerimeter(), 10 + 10 + 14.142));
	REQUIRE(DoubleEquals(triangle.GetOutlineColor(), 0xff00ff00));
	REQUIRE(DoubleEquals(triangle.GetFillColor(), 0xffffffff));

	REQUIRE_THROWS_AS(CTriangle(CPoint(0, 0), CPoint(0, 0), CPoint(0, 0)), InvalidTriangleException);
	REQUIRE_THROWS_AS(CTriangle(CPoint(0, 0), CPoint(0, 10), CPoint(0, 0)), InvalidTriangleException);
	REQUIRE_THROWS_AS(CTriangle(CPoint(10, 0), CPoint(20, 0), CPoint(30, 0)), InvalidTriangleException);

	std::stringstream output;
	CCanvasTest canvas(output);
	triangle.Draw(canvas);
	std::string outputString = "the polygon is filled in by points (0, 0) (10, 0) (0, 10)\n"
							   "line is drawn from (0, 0) to (10, 0)\n"
							   "line is drawn from (10, 0) to (0, 10)\n"
							   "line is drawn from (0, 10) to (0, 0)\n";

	REQUIRE(output.str() == outputString);
}