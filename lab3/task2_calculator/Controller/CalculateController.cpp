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
		std::cout << match[1];
		this->m_identificatorService.CreateVariableIdentificator(match[1]);
	}
	else
	{
		std::cout << "error";
		// error
	}
}

void CalculateController::CreateVariableWithValue(const CalculateCommand& command)
{
	std::regex pattern("([a-zA-Z][a-zA-Z0-9_]*)=(([a-zA-Z][a-zA-Z0-9_]*)|([+-]?\\d+(\\.\\d*)?|\\.\\d+))");
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
		std::cout << "error" << command.bodyCommand;
		// error
	}
}

void CalculateController::CreateFunction(const CalculateCommand& command)
{
	std::regex pattern("([a-zA-Z][a-zA-Z0-9_]*) = ([a-zA-Z][a-zA-Z0-9_]*) \\+ ([a-zA-Z][a-zA-Z0-9_]*)");
}

void CalculateController::PrintVariables(std::ostream& output)
{
	std::vector<IdentificatorValueData> identificatorValuesData = this->m_identificatorQueryService.GetVariableIdentificatorValuesData();
	for (const auto& identificatorValueData : identificatorValuesData)
	{
		output << identificatorValueData.identificatorName << ":" << identificatorValueData.value << std::endl;
	}
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
		PrintVariables(output);
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