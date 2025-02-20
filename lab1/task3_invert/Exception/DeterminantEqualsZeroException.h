#include <iostream>

class DeterminantEqualsZeroException : public std::runtime_error
{
public:
	DeterminantEqualsZeroException()
		: std::runtime_error("Non-invertible"){};
};