#include "main.h"

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

// TODO: Сделать через input.fail чтобы сразу из потока считывать double
void ReadNumbers(std::istream& input, std::vector<double>& numbers)
{
	double number;
	while (input >> number)
	{
		numbers.push_back(number);
	}

	if (input.fail() && !input.eof())
	{
		throw InvalidValueException();
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