#pragma once
#include "../AppCommand.h"
#include <string>

enum class CalculateCommandType
{
	VAR,
	LET,
	FN,
	PRINT,
	PRINTVARS,
	PRINTFNS,
	NONE,
};

struct CalculateCommand
{
	CalculateCommandType type = CalculateCommandType::NONE;
	std::string bodyCommand;
	CalculateCommand(CalculateCommandType type, std::string bodyCommand = "")
		: type(type)
		, bodyCommand(bodyCommand)
	{
	}
};

CalculateCommand CreateCalculateCommand(const AppCommand& appCommand);