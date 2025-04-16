#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../../../catch/catch.hpp"
#include "../../../src/Shape/Entity/CRectangle.h"
#include "../../../src/Shape/Exception/InvalidRectangleSizeException.h"
#include "../../Components/CCanvasTest.h"

bool DoubleEquals(double a, double b)
{
	const double epsilon = 1e-10;
	return std::fabs(a - a) < epsilon;
}

TEST_CASE("TestCreateRectangle")
{
	CRectangle rectangle = CRectangle(CPoint(0, 0), CPoint(10, 10), 0xff00ff00, 0xffffffff);

	REQUIRE(DoubleEquals(rectangle.GetArea(), 100));
	REQUIRE(DoubleEquals(rectangle.GetPerimeter(), 40));
	REQUIRE(DoubleEquals(rectangle.GetOutlineColor(), 0xff00ff00));
	REQUIRE(DoubleEquals(rectangle.GetFillColor(), 0xffffffff));

	REQUIRE_THROWS_AS(CRectangle(CPoint(0, 0), CPoint(10, 0)), InvalidRectangleSizeException);
	REQUIRE_THROWS_AS(CRectangle(CPoint(0, 0), CPoint(0, 10)), InvalidRectangleSizeException);
	REQUIRE_THROWS_AS(CRectangle(CPoint(10, 0), CPoint(0, 0)), InvalidRectangleSizeException);
	REQUIRE_THROWS_AS(CRectangle(CPoint(0, 10), CPoint(0, 0)), InvalidRectangleSizeException);
	REQUIRE_THROWS_AS(CRectangle(CPoint(0, 0), CPoint(0, 0)), InvalidRectangleSizeException);

	std::stringstream output;
	CCanvasTest canvas(output);
	rectangle.Draw(canvas);
	std::string outputString = "the polygon is filled in by points (0, 0) (10, 0) (10, 10) (0, 10)\n"
							   "line is drawn from (0, 0) to (10, 0)\n"
							   "line is drawn from (10, 0) to (10, 10)\n"
							   "line is drawn from (10, 10) to (0, 10)\n"
							   "line is drawn from (0, 10) to (0, 0)\n";
	REQUIRE(output.str() == outputString);
}