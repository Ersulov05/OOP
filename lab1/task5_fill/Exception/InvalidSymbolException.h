#include <iostream>

class InvalidSymbolException : public std::runtime_error
{
public:
	InvalidSymbolException()
		: std::runtime_error("Invalid symbol"){};
};