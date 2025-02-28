#include "Exception/InvalidValueException.h"
#include "Vector.h"

const int NUMBER_OF_DECIMAL_PLACES = 3;

void PrintSortedNumbers(std::ostream& output, const std::vector<double>& numbers)
{
	std::vector<double> sortedNumbers = numbers;
	std::sort(sortedNumbers.begin(), sortedNumbers.end());

	output << std::fixed << std::setprecision(NUMBER_OF_DECIMAL_PLACES);
	for (size_t i = 0; i < sortedNumbers.size(); ++i)
	{
		output << sortedNumbers[i];
		if (i < sortedNumbers.size() - 1)
		{
			output << " ";
		}
	}
}

// TODO: Сделать через input.fail чтобы сразу из потока считывать double не делая проверку
std::vector<double> ReadNumbers(std::istream& input)
{
	std::vector<double> numbers;
	double number;
	while (input >> number)
	{
		numbers.push_back(number);
	}

	if (input.fail() && !input.eof())
	{
		throw InvalidValueException();
	}
	return numbers;
}

int main(int argc, char* argv[])
{
	try
	{
		std::vector<double> numbers = ReadNumbers(std::cin);
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