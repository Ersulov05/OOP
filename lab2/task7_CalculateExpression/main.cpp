#include "./Exception/InvalidExpressionException.h"
#include "./Utils/Element.h"
#include "./Utils/NumberUtils.h"
#include "CalculateExpression.h"
#include <iostream>
#include <stack>

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

bool SkipSpaces(std::istream& input)
{
	char ch = '\0';
	while (input.get(ch) && ch == ' ')
	{
	}
	input.unget();
	return true;
}

bool AreInputEOLN(std::istream& input)
{
	char ch;
	input.get(ch);
	bool eof = input.eof();
	input.unget();
	return ch == '\n' || eof;
}

void CalculateExpression(std::istream& input, std::ostream& output)
{
	std::stack<Element> expression;
	while (SkipSpaces(input) && !AreInputEOLN(input))
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