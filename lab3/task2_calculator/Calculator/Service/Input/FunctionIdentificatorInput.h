#pragma once
#include <optional>

struct FunctionIdentificatorInput
{
	std::string identificatorName;
	std::string firstIdentificatorName;
	std::optional<std::string> operation = std::nullopt;
	std::string secondIdentificatorName;

	FunctionIdentificatorInput(std::string identificatorName, std::string firstIdentificatorName, std::string operation, std::string secondIdentificatorName)
		: identificatorName(identificatorName)
		, firstIdentificatorName(firstIdentificatorName)
		, operation(operation)
		, secondIdentificatorName(secondIdentificatorName){};

	FunctionIdentificatorInput(std::string identificatorName, std::string firstIdentificatorName)
		: identificatorName(identificatorName)
		, firstIdentificatorName(firstIdentificatorName){};
};