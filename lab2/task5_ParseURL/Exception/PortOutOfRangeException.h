#include <iostream>
#include <string>

class PortOutOfRangeException : public std::runtime_error
{
public:
	PortOutOfRangeException(int minPort, int maxPort)
		: std::runtime_error("Port out of range " + std::to_string(minPort) + " - " + std::to_string(maxPort)){};
};