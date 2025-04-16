#define CATCH_CONFIG_MAIN
#include "../../../../../catch/catch.hpp"
#include "../../../src/Shape/Entity/CLineSegment.h"
#include "../../Components/CCanvasTest.h"

bool DoubleEquals(double a, double b)
{
	const double epsilon = 1e-10;
	return std::fabs(a - a) < epsilon;
}

TEST_CASE("TestCreateLineSegment")
{
	CLineSegment line = CLineSegment(CPoint(0, 0), CPoint(10, 0), 0xff00ff00);

	REQUIRE(DoubleEquals(line.GetArea(), 0));
	REQUIRE(DoubleEquals(line.GetPerimeter(), 10));
	REQUIRE(DoubleEquals(line.GetOutlineColor(), 0xff00ff00));

	std::stringstream output;
	CCanvasTest canvas(output);
	line.Draw(canvas);
	REQUIRE(output.str() == "line is drawn from (0, 0) to (10, 0)\n");
}