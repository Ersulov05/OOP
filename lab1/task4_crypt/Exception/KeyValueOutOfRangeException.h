#include <iostream>

class KeyValueOutOfRangeException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "The value is out of range 0 - 255";
	}
};