#include "CalculateController.h"
#include "../Calculator/Entity/Operation.h"
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

const std::string IDENTIFICATOR_VALUE_SEPARATOR = ":";
const std::string IDENTIFIER_PATTERN = "[a-zA-Z][a-zA-Z0-9_]*";
const std::string OPERATION_PATTERN = "[+*/-]";
const std::string VALUE_PATTERN = "[+-]?\\d+(\\.\\d*)?|\\.\\d+";

CalculateController::CalculateController()
	: m_identificatorRepository(IdentificatorRepository())
	, m_identificatorQueryService(IdentificatorQueryService(m_identificatorRepository))
	, m_identificatorService(IdentificatorService(m_identificatorRepository))
{
}

void CalculateController::LoadIdentificators()
{
	this->m_identificatorService.StoreVariableIdentificatorByValue("x", 1);
	this->m_identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput("fn1", Operation::NONE, "x", ""));
	for (int i = 2; i < 1000000; ++i)
	{
		this->m_identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput(
			"fn" + std::to_string(i),
			Operation::PLUS,
			"fn" + std::to_string(i - 1),
			"x"));
	}
}

void CalculateController::CreateVariable(const CalculateCommand& command)
{
	std::regex pattern("^(" + IDENTIFIER_PATTERN + ")?$");
	std::smatch match;

	if (std::regex_match(command.bodyCommand, match, pattern))
	{
		this->m_identificatorService.CreateVariableIdentificator(match[1]);
	}
	else
	{
		std::cout << "error";
	}
}

void CalculateController::CreateVariableWithValue(const CalculateCommand& command)
{
	std::regex pattern("^(" + IDENTIFIER_PATTERN + ")=((" + IDENTIFIER_PATTERN + ")|(" + VALUE_PATTERN + "))?$");
	std::smatch match;
	if (std::regex_match(command.bodyCommand, match, pattern))
	{
		if (match[3].matched)
		{
			this->m_identificatorService.StoreVariableIdentificatorByIdentificator(match[1], match[3]);
			return;
		}
		float value = std::stof(match[4].str());
		this->m_identificatorService.StoreVariableIdentificatorByValue(match[1], value);
		this->m_identificatorQueryService.ClearCache();
	}
	else
	{
		std::cout << "error" << command.bodyCommand;
	}
}

void CalculateController::CreateFunction(const CalculateCommand& command)
{
	std::regex pattern("^(" + IDENTIFIER_PATTERN + ")=(" + IDENTIFIER_PATTERN + ")" + "(?:(" + OPERATION_PATTERN + ")(" + IDENTIFIER_PATTERN + "))?$");
	std::smatch match;
	if (std::regex_match(command.bodyCommand, match, pattern))
	{
		std::string identificatorName = match[1];
		std::string firstIdentificatorName = match[2];
		Operation operation = Operation::NONE;
		std::string secondIdentificatorName;
		if (match[3].matched)
		{
			operation = GetOperationByString(match[3]);
			secondIdentificatorName = match[4];
		}
		this->m_identificatorService.CreateFunctionIdentificator(FunctionIdentificatorInput(identificatorName, operation, firstIdentificatorName, secondIdentificatorName));
	}
	else
	{
		std::cout << "error" << command.bodyCommand;
	}
}

void CalculateController::PrintIdentificatorValuesData(std::ostream& output, const std::vector<IdentificatorValueData>& identificatorValuesData)
{
	for (const auto& identificatorValueData : identificatorValuesData)
	{
		output << identificatorValueData.identificatorName << IDENTIFICATOR_VALUE_SEPARATOR << identificatorValueData.value << std::endl;
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
		PrintIdentificatorValuesData(output, { this->m_identificatorQueryService.GetIdentificatorValueData(command.bodyCommand) });
		break;
	case CalculateCommandType::PRINTVARS:
		PrintIdentificatorValuesData(output, this->m_identificatorQueryService.GetVariableIdentificatorValuesData());
		break;
	case CalculateCommandType::PRINTFNS:
		PrintIdentificatorValuesData(output, this->m_identificatorQueryService.GetFunctionIdentificatorValuesData());
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