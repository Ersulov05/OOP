#include <iostream>

class InvalidKeyValueException : public std::runtime_error
{
public:
	InvalidKeyValueException()
		: std::runtime_error("Invalid key value"){};
};