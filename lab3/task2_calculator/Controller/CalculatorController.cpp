#include "CalculatorController.h"
#include "../Calculator/Entity/Operation.h"
#include "../Calculator/Service/Input/FunctionIdentificatorInput.h"
#include "./Exception/InvalidCalculatorCommandArgumentsException.h"
#include "./Exception/UnknownCalculatorCommandException.h"
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>

const std::string IDENTIFICATOR_VALUE_SEPARATOR = ":";
const std::string IDENTIFIER_PATTERN = "[a-zA-Z][a-zA-Z0-9_]*";
const std::string OPERATION_PATTERN = "[+*/-]";
const std::string VALUE_PATTERN = "[+-]?\\d+(\\.\\d*)?|\\.\\d+";

CalculatorController::CalculatorController()
	: m_identificatorQueryService(IdentificatorQueryService(m_identificatorRepository))
	, m_identificatorService(IdentificatorService(m_identificatorRepository))
{
}

void CalculatorController::HandleCalculatorCommand(std::ostream& output, const CalculatorCommand& command)
{
	try
	{
		this->ExecuteCalculatorCommand(output, command);
	}
	catch (const std::runtime_error& e)
	{
		output << e.what() << std::endl;
	}
}

void CalculatorController::CreateVariable(const CalculatorCommand& command)
{
	std::regex pattern("^\\s*(" + IDENTIFIER_PATTERN + ")\\s*?$");
	std::smatch match;

	if (!std::regex_match(command.bodyCommand, match, pattern))
	{
		throw InvalidCalculatorCommandArgumentsException();
	}

	this->m_identificatorService.CreateVariableIdentificator(match[1]);
}

void CalculatorController::CreateVariableWithValue(const CalculatorCommand& command)
{
	std::regex pattern("^\\s*(" + IDENTIFIER_PATTERN + ")\\s*=\\s*((" + IDENTIFIER_PATTERN + ")|(" + VALUE_PATTERN + "))?\\s*$");
	std::smatch match;
	if (!std::regex_match(command.bodyCommand, match, pattern))
	{
		throw InvalidCalculatorCommandArgumentsException();
	}

	if (match[3].matched)
	{
		this->m_identificatorService.StoreVariableIdentificatorByIdentificator(match[1], match[3]);
		this->m_identificatorQueryService.ClearCache();
		return;
	}
	float value = std::stof(match[4].str());
	this->m_identificatorService.StoreVariableIdentificatorByValue(match[1], value);
	this->m_identificatorQueryService.ClearCache();
}

void CalculatorController::CreateFunction(const CalculatorCommand& command)
{
	std::regex pattern("^\\s*(" + IDENTIFIER_PATTERN + ")\\s*=\\s*(" + IDENTIFIER_PATTERN + ")" + "\\s*(?:(" + OPERATION_PATTERN + ")\\s*(" + IDENTIFIER_PATTERN + "))?\\s*$");
	std::smatch match;
	if (!std::regex_match(command.bodyCommand, match, pattern))
	{
		throw InvalidCalculatorCommandArgumentsException();
	}

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

void CalculatorController::PrintIdentificatorValuesData(std::ostream& output, const std::vector<IdentificatorValueData>& identificatorValuesData)
{
	std::cout << std::fixed << std::setprecision(2);
	std::vector<IdentificatorValueData> sortedIdentificatorValuesData = identificatorValuesData;
	std::sort(sortedIdentificatorValuesData.begin(), sortedIdentificatorValuesData.end(),
		[](const IdentificatorValueData& a, const IdentificatorValueData& b) {
			return a.identificatorName < b.identificatorName;
		});

	for (const auto& identificatorValueData : sortedIdentificatorValuesData)
	{
		output << identificatorValueData.identificatorName << IDENTIFICATOR_VALUE_SEPARATOR << identificatorValueData.value << std::endl;
	}
}

void CalculatorController::ExecuteCalculatorCommand(std::ostream& output, const CalculatorCommand& command)
{
	switch (command.type)
	{
	case CalculatorCommandType::VAR:
		CreateVariable(command);
		break;
	case CalculatorCommandType::LET:
		CreateVariableWithValue(command);
		break;
	case CalculatorCommandType::FN:
		CreateFunction(command);
		break;
	case CalculatorCommandType::PRINT:
		PrintIdentificatorValuesData(output, { this->m_identificatorQueryService.GetIdentificatorValueData(GetIdentificatorName(command)) });
		break;
	case CalculatorCommandType::PRINTVARS:
		PrintIdentificatorValuesData(output, this->m_identificatorQueryService.GetVariableIdentificatorValuesData());
		break;
	case CalculatorCommandType::PRINTFNS:
		PrintIdentificatorValuesData(output, this->m_identificatorQueryService.GetFunctionIdentificatorValuesData());
		break;
	default:
		throw UnknownCalculatorCommandException();
	}
}

std::string CalculatorController::GetIdentificatorName(const CalculatorCommand& command)
{
	std::regex pattern("^\\s*(" + IDENTIFIER_PATTERN + ")\\s*?$");
	std::smatch match;

	if (!std::regex_match(command.bodyCommand, match, pattern))
	{
		throw InvalidCalculatorCommandArgumentsException();
	}
	return match[1];
}