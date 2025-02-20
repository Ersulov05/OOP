#include <iostream>

class InputOutputFileNameMatchException : public std::runtime_error
{
public:
	InputOutputFileNameMatchException()
		: std::runtime_error("Еhe name of the input file is the same as the name of the output file"){};
};