#include <iostream>

class InvalidArgumentCountException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "The number of arguments passed is incorrect";
	}
};