#include <iostream>

class InvalidSymbolException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Invalid symbol";
	}
};