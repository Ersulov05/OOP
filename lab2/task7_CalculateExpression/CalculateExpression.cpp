#include "CalculateExpression.h"

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

void AssertResultNotOutOfRangeWhenSumming(int currentValue, int addedValue)
{
	if (addedValue > 0 && currentValue > __INT_MAX__ - addedValue || addedValue < 0 && currentValue < -__INT_MAX__ - addedValue)
	{
		throw ValueOutOfRangeWhenCalculatingException();
	}
}

void AssertResultNotOutOfRangeWhenMultiplying(int currentValue, int multiplier)
{
	if (std::abs(currentValue) > __INT_MAX__ / std::abs(multiplier))
	{
		throw ValueOutOfRangeWhenCalculatingException();
	}
}

int GetSumm(const std::vector<int>& values)
{
	return std::accumulate(values.begin(), values.end(), 0, [](int acc, int value) {
		AssertResultNotOutOfRangeWhenSumming(acc, value);
		return acc + value;
	});
}

int GetComposition(const std::vector<int>& values)
{
	return std::accumulate(values.begin(), values.end(), 1, [](int acc, int value) {
		AssertResultNotOutOfRangeWhenMultiplying(acc, value);
		return acc * value;
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

Element GetElement(std::istream& input)
{
	int value = 0;
	int negativeCoef = GetNegativeCoef(input);
	bool isValue = false;
	char ch = '\0';

	while (input.get(ch))
	{
		if (IsDigit(ch))
		{
			value = AddDigitToValue(value, ch);
			isValue = true;
			continue;
		}
		if (isValue)
		{
			input.unget();
			return CreateElement(negativeCoef * value);
		}
		if (negativeCoef == -1)
		{
			throw InvalidExpressionException();
		}

		if (ch == ' ' || ch == '\t')
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