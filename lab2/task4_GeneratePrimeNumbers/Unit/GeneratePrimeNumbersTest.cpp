#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../GeneratePrimeNumbers.h"

TEST_CASE("test GeneratePrimeNumbersSet")
{
	REQUIRE(GeneratePrimeNumbersSet(10) == std::set<long>{ 2, 3, 5, 7 });
	REQUIRE(GeneratePrimeNumbersSet(-1) == std::set<long>{});
	REQUIRE(GeneratePrimeNumbersSet(0) == std::set<long>{});
	REQUIRE(GeneratePrimeNumbersSet(1) == std::set<long>{});
	REQUIRE(GeneratePrimeNumbersSet(2) == std::set<long>{ 2 });
	REQUIRE(GeneratePrimeNumbersSet(3) == std::set<long>{ 2, 3 });
	REQUIRE(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}