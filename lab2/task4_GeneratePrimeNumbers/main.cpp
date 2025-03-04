#include "./Exception/InvalidArgumentCountException.h"
#include "./Exception/InvalidValueException.h"
#include "./Exception/ValueOutOfRangeException.h"
#include "GeneratePrimeNumbers.h"
#include <iostream>

const int EXPECTED_ARG_COUNT = 2;

struct Arg
{
	long upperBound = 0;
};

void AssertExpectedArgumentCount(int argc)
{
	if (argc != EXPECTED_ARG_COUNT)
	{
		throw InvalidArgumentCountException();
	}
}

Arg ParseArgs(int argc, char* argv[])
{
	AssertExpectedArgumentCount(argc);

	Arg arg;
	try
	{
		arg.upperBound = std::stol(argv[1]);
	}
	catch (const std::invalid_argument& e)
	{
		throw InvalidValueException();
	}
	catch (const std::out_of_range& e)
	{
		throw ValueOutOfRangeException();
	}

	return arg;
}

void PrintPrimeNumbers(std::ostream& output, const std::set<long>& primeNumbers, const std::string& separator)
{
	for (long primeNumber : primeNumbers)
	{
		output << primeNumber << separator;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Arg arg = ParseArgs(argc, argv);
		std::set<long> primeNumbers;
		GeneratePrimeNumbersSet(arg.upperBound, primeNumbers);
		PrintPrimeNumbers(std::cout, primeNumbers, "\n");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}