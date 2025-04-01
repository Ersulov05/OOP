#pragma once
#include "Operation.h"
#include <cmath>
#include <string>
#include <variant>

enum class IdentificatorType
{
	FUNCTION,
	VARIABLE
};

struct Function
{
	Operation operation = Operation::NONE;
	std::string firstIdentificatorName;
	std::string secondIdentificatorName;

	Function(Operation operation, const std::string& firstIdentificatorName, const std::string& secondIdentificatorName)
		: operation(operation)
		, firstIdentificatorName(firstIdentificatorName)
		, secondIdentificatorName(secondIdentificatorName)
	{
	}
};

struct Identificator
{
	std::string name;
	IdentificatorType type;
	union
	{
		Function* function;
		double value = NAN;
	} data;

	// Identificator(std::string name, Function function)
	// 	: name(name)
	// 	, type(IdentificatorType::FUNCTION)
	// 	, data({ function, NAN })
	// {
	// }

	// Identificator(std::string name, double value)
	// 	: name(name)
	// 	, type(IdentificatorType::VARIABLE)
	// 	, data({ std::nullopt, value })
	// {
	// }
};
