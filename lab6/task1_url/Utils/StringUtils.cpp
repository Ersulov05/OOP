#include "StringUtils.h"

std::string GetLowerCase(const std::string& string)
{
	std::string lowerCaseString;
	for (char symbol : string)
	{
		lowerCaseString += std::tolower(symbol);
	}

	return lowerCaseString;
}