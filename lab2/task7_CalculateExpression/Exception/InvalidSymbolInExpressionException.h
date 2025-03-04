#include <iostream>

class InvalidSymbolInExpressionException : public std::runtime_error
{
public:
	InvalidSymbolInExpressionException(char ch)
		: std::runtime_error("Invalid symbol in expression \"" + std::string(1, ch) + "\""){};
};