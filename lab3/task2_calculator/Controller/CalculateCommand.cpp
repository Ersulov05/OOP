#include "./CalculateCommand.h"
#include <algorithm>

std::string GetStringWithoutSpaces(const std::string& string)
{
	std::string result = string;
	result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
	return result;
}

CalculateCommand CreateCalculateCommand(const AppCommand& appCommand)
{
	CalculateCommandType calculateCommandType = CalculateCommandType::NONE;
	if (appCommand.stringCommand == "var")
	{
		calculateCommandType = CalculateCommandType::VAR;
	}
	else if (appCommand.stringCommand == "let")
	{
		calculateCommandType = CalculateCommandType::LET;
	}
	else if (appCommand.stringCommand == "printvars")
	{
		calculateCommandType = CalculateCommandType::PRINTVARS;
	}

	std::string bodyCommand = GetStringWithoutSpaces(appCommand.bodyCommand);
	return CalculateCommand(calculateCommandType, bodyCommand);
}