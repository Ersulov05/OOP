#include <iostream>

class InvalidPortException : public std::invalid_argument
{
public:
	InvalidPortException(const std::string& port)
		: std::invalid_argument("Invalid port \"" + port + "\""){};
};