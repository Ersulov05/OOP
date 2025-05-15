#include <iostream>

class InvalidProtocolException : public std::invalid_argument
{
public:
	InvalidProtocolException(const std::string& protocol = "")
		: std::invalid_argument("Invalid protocol \"" + protocol + "\""){};
};