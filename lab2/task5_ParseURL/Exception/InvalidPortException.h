#include <iostream>

class InvalidPortException : public std::runtime_error
{
public:
	InvalidPortException(const std::string& port)
		: std::runtime_error("Invalid port \"" + port + "\""){};
};