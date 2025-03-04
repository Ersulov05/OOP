#include "GeneratePrimeNumbers.h"

void GetIsPrimeNumbers(long upperBound, std::vector<bool>& isPrime)
{
	isPrime.assign(upperBound + 1, true);
	isPrime[0] = isPrime[1] = false;

	for (long i = 4; i <= upperBound; i += 2)
	{
		isPrime[i] = false;
	}

	for (long i = 3; i * i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			for (long j = i * i; j <= upperBound; j += 2 * i)
			{
				isPrime[j] = false;
			}
		}
	}
}

void GeneratePrimeNumbersSet(long upperBound, std::set<long>& primeNumbers)
{
	if (upperBound < 2)
		return;
	std::vector<bool> isPrime;
	GetIsPrimeNumbers(upperBound, isPrime);

	for (long i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			primeNumbers.insert(i);
		}
	}
}