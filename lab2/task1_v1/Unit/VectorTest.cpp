#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Vector.h"

// SCENARIO("first test")
// {
// 	std::vector<double> numbers = { 3.5, 5.5, -1 };
// 	double summPositiveElements = GetSummPositiveElements(numbers);
// 	REQUIRE(summPositiveElements == 9);
// }

TEST_CASE("test get the sum of the positive elements of the vector")
{
	std::vector<double> numbers = { 3.5, 5, -1 };
	REQUIRE(GetSummPositiveElements(numbers) == 8.5);

	numbers = { -3.5, -5.5, -1, 0 };
	REQUIRE(GetSummPositiveElements(numbers) == 0);

	numbers = {};
	REQUIRE(GetSummPositiveElements(numbers) == 0);
}

TEST_CASE("test get the number of positive elements of a vector")
{
	std::vector<double> numbers = { 3.5, 5, -1 };
	REQUIRE(GetCountPositiveElements(numbers) == 2);

	numbers = { -3.5, -5.5, -1, 0 };
	REQUIRE(GetCountPositiveElements(numbers) == 0);

	numbers = {};
	REQUIRE(GetCountPositiveElements(numbers) == 0);
}

TEST_CASE("test get the process vector of positive elements of a vector")
{
	std::vector<double> numbers = { 3.5, 4.5, -1 };
	REQUIRE(ProcessNumbers(numbers) == std::vector<double>{ 7.5, 8.5, 3 });

	numbers = { -3.5, -4.5, -1, 0 };
	REQUIRE(ProcessNumbers(numbers) == std::vector<double>{ -3.5, -4.5, -1, 0 });

	numbers = {};
	REQUIRE(ProcessNumbers(numbers) == std::vector<double>{});
}