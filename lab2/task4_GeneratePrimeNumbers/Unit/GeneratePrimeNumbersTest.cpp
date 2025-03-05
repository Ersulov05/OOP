#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../GeneratePrimeNumbers.h"

TEST_CASE("test GeneratePrimeNumbersSet")
{
	std::set<long> primeNumbers;
	GeneratePrimeNumbersSet(10, primeNumbers);
	REQUIRE(primeNumbers == std::set<long>{ 2, 3, 5, 7 });

	GeneratePrimeNumbersSet(-1, primeNumbers);
	REQUIRE(primeNumbers == std::set<long>{});

	GeneratePrimeNumbersSet(0, primeNumbers);
	REQUIRE(primeNumbers == std::set<long>{});

	GeneratePrimeNumbersSet(1, primeNumbers);
	REQUIRE(primeNumbers == std::set<long>{});

	GeneratePrimeNumbersSet(2, primeNumbers);
	REQUIRE(primeNumbers == std::set<long>{ 2 });

	GeneratePrimeNumbersSet(3, primeNumbers);
	REQUIRE(primeNumbers == std::set<long>{ 2, 3 });

	GeneratePrimeNumbersSet(100000000, primeNumbers);
	REQUIRE(primeNumbers.size() == 5761455);
}