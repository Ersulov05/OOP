#include <iostream>

class DeterminantEqualsZeroException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Non-invertible"; //"Determinant matrix equals zero";
	}
};