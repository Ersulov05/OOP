#pragma once
#include "../Exception/InvalidSymbolInExpressionException.h"

enum class ElementType
{
	OPERATION,
	VALUE,
	OPEN_BRACKET,
	CLOSE_BRACKET,
};

enum class Operation
{
	PLUS,
	MULTIPLY
};

struct Element
{
	ElementType type;
	union
	{
		int value;
		Operation operation;
	} data;
};

Element CreateOpenBracketElement();
Element CreateCloseBracketElement();
Element CreateElement(Operation operation);
Element CreateElement(int value);
Element CharToElement(char ch);