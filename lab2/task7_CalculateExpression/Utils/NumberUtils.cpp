#include "NumberUtils.h"

bool IsDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

void AssertDigit(char ch)
{
	if (!IsDigit(ch))
	{
		throw std::runtime_error("Not digit");
	}
}

int GetDigit(char ch)
{
	AssertDigit(ch);
	return ch - '0';
}

int GetNegativeCoef(std::istream& input)
{
	char ch = '\0';
	input.get(ch);

	if (ch != '-')
	{
		input.unget();
		return 1;
	}

	return -1;
}

int AddDigitToValue(int value, char ch)
{
	// __INT_MAX__ // 2147483647
	int digit = GetDigit(ch);
	if (value > (__INT_MAX__ - digit) / RADIX)
	{
		throw ValueOutOfRangeException();
	}

	return value * RADIX + digit;
}