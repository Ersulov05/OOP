#include <iostream>

class InvalidDomainException : public std::invalid_argument
{
public:
	InvalidDomainException(const std::string& domain)
		: std::invalid_argument("Invalid domain \"" + domain + "\""){};
};