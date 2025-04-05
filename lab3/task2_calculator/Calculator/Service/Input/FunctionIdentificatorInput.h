#pragma once

struct FunctionIdentificatorInput
{
	std::string identificatorName;
	std::string firstIdentificatorName;
	std::optional<std::string> operation;
	std::string secondIdentificatorName;

	FunctionIdentificatorInput(std::string identificatorName, std::string firstIdentificatorName, std::string operation, std::string secondIdentificatorName)
		: identificatorName(identificatorName)
		, operation(operation)
		, firstIdentificatorName(firstIdentificatorName)
		, secondIdentificatorName(secondIdentificatorName){};

	FunctionIdentificatorInput(std::string identificatorName, std::string firstIdentificatorName)
		: identificatorName(identificatorName)
		, firstIdentificatorName(firstIdentificatorName){};
};