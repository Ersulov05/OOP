#include "CalculateController.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

CalculateController::CalculateController(IdentificatorRepository& identificatorRepository)
	: m_identificatorQueryService(IdentificatorQueryService(identificatorRepository))
	, m_identificatorService(IdentificatorService(identificatorRepository))
{
}

void CalculateController::CreateVariable(const CalculateCommand& command)
{
	std::regex pattern("([a-zA-Z][a-zA-Z0-9_]*)");
	std::smatch match;

	if (std::regex_match(command.bodyCommand, match, pattern))
	{
		this->m_identificatorService.CreateVariableIdentificator(match[1]);
	}
	else
	{
		// error
	}

	// std::stringstream input;
	// input.str(command.bodyCommand);

	// std::string identificatorName = GetIdentificatorName(input);
	// this->m_identificatorService.CreateVariableIdentificator(identificatorName);
}

void CalculateController::CreateVariableWithValue(const CalculateCommand& command)
{
	std::regex pattern("([a-zA-Z][a-zA-Z0-9_]*) = (([a-zA-Z][a-zA-Z0-9_]*)|([+-]?\\d+(\\.\\d*)?|\\.\\d+))");
	std::smatch match;
	if (std::regex_match(command.bodyCommand, match, pattern))
	{
		this->m_identificatorService.CreateVariableIdentificator(match[1]);
		if (match[3].matched)
		{
			this->m_identificatorService.EditVariableIdentificatorByIdentificator(match[1], match[3]);
		}
		else if (match[4].matched)
		{
			float value = std::stof(match[4].str());
			this->m_identificatorService.EditVariableIdentificatorByValue(match[1], value);
		}
	}
	else
	{
		// error
	}
	// std::stringstream input;
	// input.str(command.bodyCommand);

	// std::string identificatorName = GetIdentificatorName(input);
	// float value = GetValue(input);
	// this->m_identificatorService.CreateVariableIdentificator(identificatorName);
	// this->m_identificatorService.EditVariableIdentificatorByValue(identificatorName, value);
}

void CalculateController::CreateFunction(const CalculateCommand& command)
{
	std::regex pattern("([a-zA-Z][a-zA-Z0-9_]*) = ([a-zA-Z][a-zA-Z0-9_]*) \\+ ([a-zA-Z][a-zA-Z0-9_]*)");
	std::stringstream input;
	input.str(command.bodyCommand);

	std::string identificatorName = GetIdentificatorName(input);
	ClearEquals(input);
	std::string firstIdentificatorName = GetIdentificatorName(input);
	Operation operation = Operation::NONE;
	std::string secondIdentificatorName;

	if (input.eof())
	{
		operation = GetOperation(input);
		secondIdentificatorName = GetIdentificatorName(input);
	}

	this->m_identificatorService.CreateFunctionIdentificator(
		FunctionIdentificatorInput(
			identificatorName,
			Operation::NONE,
			firstIdentificatorName,
			secondIdentificatorName));
}

std::string GetIdentificatorName(std::istream& input)
{
	char ch;
	input.get(ch);
	AssertSymbolIsEngleshLetter(ch);
	std::string identificatorName = std::string(1, ch);
	while (input.get(ch))
	{
	}
}

void AssertSymbolIsEngleshLetter(char symbol)
{
}

Operation GetOperation(std::istream& input)
{
	char ch;
	input.get(ch);
	// convert char to operation
}

float GetValue(std::istream& input)
{
}

void ClearEquals(std::istream& input)
{
	char ch;
	input.get(ch);
}

void CalculateController::ExecuteCalculateCommand(std::ostream& output, const CalculateCommand& command)
{
	switch (command.type)
	{
	case CalculateCommandType::VAR:
		CreateVariable(command);
		break;
	case CalculateCommandType::LET:
		CreateVariableWithValue(command);
		break;
	case CalculateCommandType::FN:
		CreateFunction(command);
		break;
	case CalculateCommandType::PRINT:
		break;
	case CalculateCommandType::PRINTVARS:
		break;
	case CalculateCommandType::PRINTFNS:
		break;
	default:
		output << "Unknown command" << std::endl;
		break;
	}
}

void handleException(const std::exception& e)
{
	std::cout << e.what() << std::endl;
}

void CalculateController::HandleCalculateCommand(std::ostream& output, const CalculateCommand& command)
{
	try
	{
		this->ExecuteCalculateCommand(output, command);
	}
	catch (const std::runtime_error& e)
	{
		handleException(e);
	}
}