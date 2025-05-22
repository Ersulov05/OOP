#include <iostream>
#include <string>

class PortOutOfRangeException : public std::invalid_argument
{
public:
	PortOutOfRangeException(int minPort, int maxPort)
		: std::invalid_argument("Port out of range " + std::to_string(minPort) + " - " + std::to_string(maxPort)){};
};