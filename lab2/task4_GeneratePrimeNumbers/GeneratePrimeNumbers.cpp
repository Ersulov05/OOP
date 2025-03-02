#include "GeneratePrimeNumbers.h"

std::vector<bool> GetIsPrimeNumbers(long upperBound)
{
	std::vector<bool> isPrime(upperBound + 1, true);
	isPrime[0] = isPrime[1] = false;

	for (long i = 2; i * i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			for (long j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	return isPrime;
}

std::set<long> GeneratePrimeNumbersSet(long upperBound)
{
	if (upperBound < 2)
		return {};
	std::vector<bool> isPrime = GetIsPrimeNumbers(upperBound);
	std::set<long> primeNumbers;

	for (long i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			primeNumbers.insert(i);
		}
	}

	return primeNumbers;
}