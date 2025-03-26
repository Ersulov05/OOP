#include "CalculateController.h"
#include <iostream>
#include <string>

CalculateController::CalculateController(IdentificatorRepository& identificatorRepository)
	: m_identificatorQueryService(IdentificatorQueryService(identificatorRepository))
	, m_identificatorService(IdentificatorService(identificatorRepository))
{
}

void CalculateController::ExecuteCalculateCommand(std::ostream& output, const CalculateCommand& command)
{
	switch (command.type)
	{
	case CalculateCommandType::VAR:
		break;
	case CalculateCommandType::LET:
		break;
	case CalculateCommandType::FN:
		break;
	case CalculateCommandType::PRINT:
		break;
	case CalculateCommandType::PRINTVARS:
		break;
	case CalculateCommandType::PRINTFNS:
		break;
	default:
		std::cout << "Unknown command" << std::endl;
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