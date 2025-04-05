#include "./CalculatorCommand.h"

CalculatorCommand CreateCalculatorCommand(const AppCommand& appCommand)
{
	CalculatorCommandType calculatorCommandType = CalculatorCommandType::NONE;
	if (appCommand.stringCommand == "var")
	{
		calculatorCommandType = CalculatorCommandType::VAR;
	}
	else if (appCommand.stringCommand == "let")
	{
		calculatorCommandType = CalculatorCommandType::LET;
	}
	else if (appCommand.stringCommand == "printvars")
	{
		calculatorCommandType = CalculatorCommandType::PRINTVARS;
	}
	else if (appCommand.stringCommand == "printfns")
	{
		calculatorCommandType = CalculatorCommandType::PRINTFNS;
	}
	else if (appCommand.stringCommand == "fn")
	{
		calculatorCommandType = CalculatorCommandType::FN;
	}
	else if (appCommand.stringCommand == "print")
	{
		calculatorCommandType = CalculatorCommandType::PRINT;
	}
	std::string bodyCommand = appCommand.bodyCommand;

	return CalculatorCommand(calculatorCommandType, bodyCommand);
}