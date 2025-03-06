#include "GeneratePrimeNumbers.h"
#include <vector>

const int FIRST_NOT_PRIME_NUMBER = 4;
const int FIRST_PRIME_NUMBER = 2;
const int FIRST_ODD_PRIME_NUMBER = 3;
const int ODD_STEP = 2;

void GetIsPrimeNumbers(long upperBound, std::vector<bool>& isPrime)
{
	isPrime.assign(upperBound + 1, true);
	isPrime[0] = isPrime[1] = false;

	for (long i = FIRST_NOT_PRIME_NUMBER; i <= upperBound; i += ODD_STEP) // TODO: Вынести все магические числа
	{
		isPrime[i] = false;
	}

	for (long i = FIRST_ODD_PRIME_NUMBER; i * i <= upperBound; i += ODD_STEP)
	{
		if (isPrime[i])
		{
			for (long j = i * i; j <= upperBound; j += ODD_STEP * i)
			{
				isPrime[j] = false;
			}
		}
	}
}

void GeneratePrimeNumbersSet(long upperBound, std::set<long>& primeNumbers)
{
	primeNumbers.clear();
	if (upperBound < FIRST_PRIME_NUMBER)
		return;
	std::vector<bool> isPrime;
	GetIsPrimeNumbers(upperBound, isPrime);

	primeNumbers.insert(FIRST_PRIME_NUMBER);
	for (long i = FIRST_ODD_PRIME_NUMBER; i <= upperBound; i += ODD_STEP)
	{
		if (isPrime[i])
		{
			primeNumbers.insert(i);
		}
	}
}