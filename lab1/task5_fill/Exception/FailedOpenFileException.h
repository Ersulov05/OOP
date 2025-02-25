#include <iostream>

class FailedOpenFileException : public std::runtime_error
{
public:
	FailedOpenFileException()
		: std::runtime_error("Failed open file"){};
};