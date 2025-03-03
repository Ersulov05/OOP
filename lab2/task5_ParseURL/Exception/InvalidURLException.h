#include <iostream>

class InvalidURLException : public std::runtime_error
{
public:
	InvalidURLException(const std::string& url)
		: std::runtime_error("Invalid URL \"" + url + "\""){};
};