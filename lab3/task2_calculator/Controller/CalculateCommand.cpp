#include "./CalculateCommand.h"
#include <algorithm>

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

	return CalculateCommand(calculateCommandType, GetStringWithoutSpaces(appCommand.bodyCommand));
}

std::string GetStringWithoutSpaces(const std::string& string)
{
	std::string result = string;
	result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
	return result;
}