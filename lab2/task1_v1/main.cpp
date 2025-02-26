#include "Exception/InvalidValueException.h"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <regex>
#include <vector>

const int NUMBER_OF_DECIMAL_PLACES = 3;

double RoundToDecimal(double number, int decimals)
{
	double factor = std::pow(10, decimals);
	return std::round(number * factor) / factor;
}

void AssertStringCanConvertedToDouble(const std::string& string)
{
	const std::regex doubleRegex(R"([+-]?\d+(?:\.\d+)?(?:[eE][+-]?\d+)?)");

	if (!std::regex_match(string, doubleRegex))
	{
		throw InvalidValueException();
	}
}

double StringToDouble(const std::string& string)
{
	AssertStringCanConvertedToDouble(string);
	return std::stod(string);
}

void ReadNumbers(std::istream& input, std::vector<double>& numbers)
{
	std::string item;
	while (input >> item)
	{
		double number = StringToDouble(item);
		numbers.push_back(number);
	}
}

double GetSummPositiveElements(const std::vector<double>& numbers)
{
	return std::accumulate(numbers.begin(), numbers.end(), 0.0, [](double acc, double value) {
		return value > 0 ? acc + value : acc;
	});
}

int GetCountPositiveElements(const std::vector<double>& numbers)
{
	return std::count_if(numbers.begin(), numbers.end(), [](double value) {
		return value > 0;
	});
}

std::vector<double> ProcessNumbers(const std::vector<double>& numbers)
{
	double sum = GetSummPositiveElements(numbers);
	int count = GetCountPositiveElements(numbers);
	std::vector<double> result = numbers;
	if (count > 0)
	{
		double avr = sum / count;
		std::transform(result.begin(), result.end(), result.begin(), [avr](double value) {
			return value + avr;
		});
	}
	return result;
}

void PrintSortedNumbers(std::ostream& output, const std::vector<double>& numbers)
{
	std::vector<double> sortedNumbers = numbers;
	std::sort(sortedNumbers.begin(), sortedNumbers.end());

	output << std::fixed << std::setprecision(NUMBER_OF_DECIMAL_PLACES);
	for (size_t i = 0; i < sortedNumbers.size(); ++i)
	{
		output << RoundToDecimal(sortedNumbers[i], NUMBER_OF_DECIMAL_PLACES);
		if (i < sortedNumbers.size() - 1)
		{
			output << " ";
		}
	}
}

int main(int argc, char* argv[])
{
	try
	{
		std::vector<double> numbers;
		ReadNumbers(std::cin, numbers);
		std::vector<double> result = ProcessNumbers(numbers);
		PrintSortedNumbers(std::cout, result);
		std::cout << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}