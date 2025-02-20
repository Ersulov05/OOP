#include <iostream>

class InvalidKeyValueException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Invalid key value";
	}
};