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
	IdentificatorType type = IdentificatorType::VARIABLE;
	union DataUnion
	{
		Function* function;
		double value;

		DataUnion()
			: value(NAN){};
	} data;

	Identificator(std::string name, Function function)
		: name(name)
		, type(IdentificatorType::FUNCTION)
	{
		data.function = new Function(function);
	}

	Identificator(std::string name, double value)
		: name(name)
		, type(IdentificatorType::VARIABLE)
	{
		data.value = value;
	}

	Identificator(){};
};
