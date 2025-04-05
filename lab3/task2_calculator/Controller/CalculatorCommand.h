#pragma once
#include "../AppCommand.h"
#include <string>

enum class CalculatorCommandType
{
	VAR,
	LET,
	FN,
	PRINT,
	PRINTVARS,
	PRINTFNS,
	NONE,
};

struct CalculatorCommand
{
	CalculatorCommandType type = CalculatorCommandType::NONE;
	std::string bodyCommand;
	CalculatorCommand(CalculatorCommandType type, std::string bodyCommand = "")
		: type(type)
		, bodyCommand(bodyCommand)
	{
	}
};

CalculatorCommand CreateCalculatorCommand(const AppCommand& appCommand);