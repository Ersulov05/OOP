#include <iostream>

class KeyValueOutOfRangeException : public std::runtime_error
{
public:
	KeyValueOutOfRangeException()
		: std::runtime_error("The value is out of range 0 - 255"){};
};