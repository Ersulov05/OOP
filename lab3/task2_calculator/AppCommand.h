#pragma once
#include <iostream>
#include <string>
#include <vector>

struct AppCommand
{
	std::string stringCommand;
	std::string bodyCommand;
	// std::vector<std::string> stringArgs;
};

AppCommand GetAppCommand(std::istream& input);