#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../src/FindMaxEx.h"
#include <sstream>

struct Sportsmen
{
	std::string fio;
	int height = 0;
	int weight = 0;
	Sportsmen() = default;
	Sportsmen(std::string fio, int height, int weight)
		: fio(fio)
		, height(height)
		, weight(weight)
	{
	}
};

bool CompareByHeight(const Sportsmen& a, const Sportsmen& b)
{
	return a.height < b.height;
}

bool CompareByWeight(const Sportsmen& a, const Sportsmen& b)
{
	return a.weight < b.weight;
}

TEST_CASE("testFindMaxExEmpty")
{
	std::vector<Sportsmen> sportsmens;
	Sportsmen maxSportsmen;
	REQUIRE(FindMaxEx(sportsmens, maxSportsmen, CompareByHeight) == false);
}

TEST_CASE("testFindMaxExOneElement")
{
	std::vector<Sportsmen> sportsmens = {
		Sportsmen("Maryshev Alexey", 175, 80)
	};
	Sportsmen maxSportsmen;
	REQUIRE(FindMaxEx(sportsmens, maxSportsmen, CompareByHeight) == true);
	REQUIRE(maxSportsmen.fio == "Maryshev Alexey");
	REQUIRE(maxSportsmen.height == 175);
	REQUIRE(maxSportsmen.weight == 80);

	REQUIRE(FindMaxEx(sportsmens, maxSportsmen, CompareByWeight) == true);
	REQUIRE(maxSportsmen.fio == "Maryshev Alexey");
	REQUIRE(maxSportsmen.height == 175);
	REQUIRE(maxSportsmen.weight == 80);
}

TEST_CASE("testFindMaxEx")
{
	std::vector<Sportsmen> sportsmens = {
		Sportsmen("Maryshev Alexey", 175, 80),
		Sportsmen("Ersulov Andrey", 160, 95),
		Sportsmen("Dudinov Nikita", 180, 70),
		Sportsmen("Belyaev Dmitriy", 165, 65)
	};
	Sportsmen maxSportsmen;
	REQUIRE(FindMaxEx(sportsmens, maxSportsmen, CompareByHeight) == true);
	REQUIRE(maxSportsmen.fio == "Dudinov Nikita");
	REQUIRE(maxSportsmen.height == 180);
	REQUIRE(maxSportsmen.weight == 70);
}