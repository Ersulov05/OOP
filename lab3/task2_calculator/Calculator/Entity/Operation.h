#pragma once
#include <string>

enum class Operation
{
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDING,
	NONE
};

Operation GetOperationByString(const std::string& str);