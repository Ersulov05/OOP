#include "./src/FindMaxEx.h"
#include <iostream>

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

void PrintSportsmen(std::ostream& output, const Sportsmen& sportsmen)
{
	output << sportsmen.fio << " " << sportsmen.height << " " << sportsmen.weight;
}

bool CompareByHeight(const Sportsmen& a, const Sportsmen& b)
{
	return a.height < b.height;
}

bool CompareByWeight(const Sportsmen& a, const Sportsmen& b)
{
	return a.weight < b.weight;
}

bool CompareByFIO(const Sportsmen& a, const Sportsmen& b)
{
	return a.fio < b.fio;
}

int main()
{
	std::vector<Sportsmen> sportsmens;
	sportsmens.push_back(Sportsmen("Maryshev Alexey", 175, 80));
	sportsmens.push_back(Sportsmen("Ersulov Andrey", 160, 95));
	sportsmens.push_back(Sportsmen("Dudinov Nikita", 180, 70));
	sportsmens.push_back(Sportsmen("Belyaev Dmitriy", 165, 65));

	Sportsmen maxSportsmen;

	if (FindMaxEx(sportsmens, maxSportsmen, CompareByHeight))
	{
		std::cout << "Sportsmen with max height ";
		PrintSportsmen(std::cout, maxSportsmen);
		std::cout << std::endl;
	}

	if (FindMaxEx(sportsmens, maxSportsmen, CompareByWeight))
	{
		std::cout << "Sportsmen with max weight ";
		PrintSportsmen(std::cout, maxSportsmen);
		std::cout << std::endl;
	}

	if (FindMaxEx(sportsmens, maxSportsmen, CompareByFIO))
	{
		std::cout << "Sportsmen with max FIO ";
		PrintSportsmen(std::cout, maxSportsmen);
		std::cout << std::endl;
	}

	return 0;
}