#include "GeneratePrimeNumbers.h"
#include <vector>

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
	primeNumbers.clear();
	if (upperBound < 2)
		return;
	std::vector<bool> isPrime;
	GetIsPrimeNumbers(upperBound, isPrime);

	primeNumbers.insert(2);
	for (long i = 3; i <= upperBound; i += 2)
	{
		if (isPrime[i])
		{
			primeNumbers.insert(i);
		}
	}
}