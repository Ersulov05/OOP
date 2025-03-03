#include <iostream>

class InvalidProtocolException : public std::runtime_error
{
public:
	InvalidProtocolException(const std::string& protocol)
		: std::runtime_error("Invalid protocol \"" + protocol + "\""){};
};