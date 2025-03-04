// #include "ParseURL.h"

#include "./Exception/InvalidExpressionException.h"
#include "./Exception/InvalidSymbolInExpressionException.h"
#include "./Exception/ValueInExpressionOutOfRangeException.h"
#include "./Exception/ValueOutOfRangeException.h"
#include <iostream>
#include <numeric>
#include <optional>
#include <stack>
#include <vector>

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
	MYLTIPLY
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

Element CreateOpenBracketElement()
{
	Element element;
	element.type = ElementType::OPEN_BRACKET;
	return element;
}

Element CreateCloseBracketElement()
{
	Element element;
	element.type = ElementType::CLOSE_BRACKET;
	return element;
}

Element CreateElement(Operation operation)
{
	Element element;
	element.type = ElementType::OPERATION;
	element.data.operation = operation;
	return element;
}

Element CreateElement(int value)
{
	Element element;
	element.type = ElementType::VALUE;
	element.data.value = value;
	return element;
}

std::vector<int> GetValues(std::stack<Element>& stack)
{
	std::vector<int> values;
	Element element;
	while (!stack.empty() && (element = stack.top()).type == ElementType::VALUE)
	{
		stack.pop();
		values.push_back(element.data.value);
	}

	return values;
}

std::optional<Operation> GetOperation(std::stack<Element>& stack)
{
	Element element;
	if (stack.empty() || (element = stack.top()).type != ElementType::OPERATION)
	{
		return std::nullopt;
	}
	stack.pop();

	return element.data.operation;
}

void ClearOpenBracket(std::stack<Element>& stack)
{
	Element element;
	if (stack.empty() || (element = stack.top()).type != ElementType::OPEN_BRACKET)
	{
		throw InvalidExpressionException();
	}
	stack.pop();
}

int GetSumm(const std::vector<int>& values)
{
	return std::accumulate(values.begin(), values.end(), 0, [](int acc, int value) {
		return acc + value; // TODO: Добавить обработку переполнения
	});
}

int GetComposition(const std::vector<int>& values)
{
	return std::accumulate(values.begin(), values.end(), 1, [](int acc, int value) {
		return acc * value; // TODO: Добавить обработку переполнения
	});
}

int Calculate(std::vector<int>& values, Operation operation)
{
	switch (operation)
	{
	case Operation::PLUS:
		return GetSumm(values);
	case Operation::MYLTIPLY:
		return GetComposition(values);
	default:
		throw std::runtime_error("Unknown operation");
	}
}

int CalculateExpressionInStack(std::stack<Element>& stack)
{
	std::vector<int> values = GetValues(stack);
	std::optional<Operation> operation = GetOperation(stack);
	ClearOpenBracket(stack);
	if (operation)
	{
		return Calculate(values, *operation);
	}
	if (values.size() != 1)
	{
		throw InvalidExpressionException();
	}
	return values[0];
}

int CharToInt(char ch)
{
	return ch - '0';
}

int GetNegativeCoef(std::istream& iss)
{
	char ch = '\0';
	iss.get(ch);

	if (ch != '-')
	{
		iss.unget();
		return 1;
	}

	return -1;
}

Element CharToElement(char ch)
{
	switch (ch)
	{
	case '(':
		return CreateOpenBracketElement();
	case ')':
		return CreateCloseBracketElement();
	case '*':
		return CreateElement(Operation::MYLTIPLY);
	case '+':
		return CreateElement(Operation::PLUS);
	default:
		throw InvalidSymbolInExpressionException(ch);
	}
}

Element GetElement(std::istream& input)
{
	int value = 0;
	int negativeCoef = GetNegativeCoef(input);
	bool isValue = !negativeCoef;
	char ch = '\0';

	while (input.get(ch))
	{
		if (ch >= '0' && ch <= '9')
		{
			value = value * 10 + CharToInt(ch); // TODO: Добавить проверку переполнения
			isValue = true;
			continue;
		}
		if (isValue)
		{
			input.unget();
			return CreateElement(negativeCoef * value);
		}
		if (ch == ' ')
		{
			continue;
		}

		return CharToElement(ch);
	}
	if (!isValue) // TODO: Вынести в Assert
	{
		throw InvalidExpressionException();
	}

	return CreateElement(value);
}

void AssertCorectResultExpression(const std::stack<Element>& stack)
{
	if (!(stack.size() == 1 && stack.top().type == ElementType::VALUE))
	{
		throw InvalidExpressionException();
	}
}

int GetResultExpression(const std::stack<Element>& stack)
{
	AssertCorectResultExpression(stack);
	return stack.top().data.value;
}

bool AreInputNotEOLN(std::istream& input)
{
	char ch;
	input.get(ch);
	bool eof = input.eof();
	input.unget();

	return ch != '\n' && !eof;
}

void CalculateExpression(std::istream& input, std::ostream& output)
{
	std::stack<Element> expression;
	while (AreInputNotEOLN(input))
	{
		Element element = GetElement(input);
		if (element.type == ElementType::CLOSE_BRACKET)
		{
			int result = CalculateExpressionInStack(expression);
			element = CreateElement(result);
		}
		expression.push(element);
	}

	output << GetResultExpression(expression) << std::endl;
}

int main(int argc, char* argv[])
{
	try
	{
		CalculateExpression(std::cin, std::cout);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}