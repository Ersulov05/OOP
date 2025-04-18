#pragma once
#include <iostream>
#include <string>
#include <vector>

struct AppCommand
{
	std::string stringCommand; // TODO: Подумать над именованием
	std::vector<std::string> stringArgs;
};

AppCommand GetAppCommand(std::istream& input);