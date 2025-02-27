#define CATCH_CONFIG_MAIN
#undef MINSIGSTKSZ
#define MINSIGSTKSZ 16384
#include "../../catch/catch.hpp"
#include "main.h"

// SCENARIO("first test")
// {
// 	// std::vector<double> vector;
// 	// double summ = GetSummPositiveElements(vector);

// 	REQUIRE(0 == 0);
// }

TEST_CASE("first test")
{
	REQUIRE(0 == 0);
}