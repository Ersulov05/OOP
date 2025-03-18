#include "./AppCommand.h"
#include <sstream>

void GetStringArgs(std::istream& lineStream, std::vector<std::string>& stringArgs)
{
	std::string arg;
	while (lineStream >> arg)
	{
		stringArgs.push_back(arg);
	}
}

AppCommand GetAppCommand(std::istream& input)
{
	std::string line;
	getline(input, line);

	std::istringstream lineStream(line);
	AppCommand command;

	lineStream >> command.stringCommand;
	GetStringArgs(lineStream, command.stringArgs);

	return command;
}