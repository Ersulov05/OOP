#include "Vector.h"

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