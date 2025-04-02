#pragma once
#include "../../Entity/Operation.h"

struct FunctionIdentificatorInput
{
	std::string identificatorName;
	Operation operation;
	std::string firstIdentificatorName;
	std::string secondIdentificatorName;

	FunctionIdentificatorInput(std::string identificatorName, Operation operation, std::string firstIdentificatorName, std::string secondIdentificatorName = "")
		: identificatorName(identificatorName)
		, operation(operation)
		, firstIdentificatorName(firstIdentificatorName)
		, secondIdentificatorName(secondIdentificatorName){};
};