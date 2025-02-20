#include <iostream>

class InvalidMatrixFormatException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Invalid matrix format";
	}
};