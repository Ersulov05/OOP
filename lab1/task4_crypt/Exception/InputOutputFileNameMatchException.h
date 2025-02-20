#include <iostream>

class InputOutputFileNameMatchException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Еhe name of the input file is the same as the name of the output file";
	}
};