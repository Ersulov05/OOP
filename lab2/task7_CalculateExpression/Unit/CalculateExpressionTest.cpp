#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../CalculateExpression.h"
#include "../Utils/Element.h"

TEST_CASE("TestGetValues")
{
	std::stack<Element> stack;
	REQUIRE(GetValues(stack) == std::vector<int>{});

	stack.push(CreateElement(5));
	stack.push(CreateElement(7));

	REQUIRE(GetValues(stack) == std::vector<int>{ 7, 5 });
	REQUIRE(stack.size() == 0);

	stack.push(CreateElement(5));
	stack.push(CreateOpenBracketElement());

	REQUIRE(GetValues(stack) == std::vector<int>{});
	REQUIRE(stack.size() == 2);

	stack.push(CreateElement(7));
	stack.push(CreateElement(9));

	REQUIRE(GetValues(stack) == std::vector<int>{ 9, 7 });
	REQUIRE(stack.size() == 2);
}

TEST_CASE("TestGetOperation")
{
	std::stack<Element> stack;

	REQUIRE(GetOperation(stack) == std::nullopt);

	stack.push(CreateElement(Operation::MULTIPLY));
	REQUIRE(*GetOperation(stack) == Operation::MULTIPLY);
	REQUIRE(stack.size() == 0);

	stack.push(CreateElement(Operation::PLUS));
	REQUIRE(*GetOperation(stack) == Operation::PLUS);
	REQUIRE(stack.size() == 0);

	stack.push(CreateElement(9));
	stack.push(CreateElement(Operation::PLUS));
	REQUIRE(*GetOperation(stack) == Operation::PLUS);
	REQUIRE(stack.size() == 1);

	stack.push(CreateElement(Operation::MULTIPLY));
	stack.push(CreateElement(9));
	REQUIRE(GetOperation(stack) == std::nullopt);
	REQUIRE(stack.size() == 3);
}

TEST_CASE("TestClearOpenBracket")
{
	std::stack<Element> stack;

	REQUIRE_THROWS_AS(ClearOpenBracket(stack), InvalidExpressionException);

	stack.push(CreateOpenBracketElement());
	ClearOpenBracket(stack);
	REQUIRE(stack.size() == 0);

	stack.push(CreateOpenBracketElement());
	stack.push(CreateOpenBracketElement());
	ClearOpenBracket(stack);
	REQUIRE(stack.size() == 1);

	stack.push(CreateElement(5));
	REQUIRE_THROWS_AS(ClearOpenBracket(stack), InvalidExpressionException);
	REQUIRE(stack.size() == 2);
}

TEST_CASE("TestGetSumm")
{
	std::vector<int> numbers = { 5, 7, 9 };

	REQUIRE(GetSumm(numbers) == 21);

	numbers = {};
	REQUIRE(GetSumm(numbers) == 0);

	numbers = { -2, -3 };
	REQUIRE(GetSumm(numbers) == -5);

	numbers = { -2, 2 };
	REQUIRE(GetSumm(numbers) == 0);

	numbers = { 1, 2147483647 }; // TODO: использовать __INT_MAX
	REQUIRE_THROWS_AS(GetSumm(numbers), ValueOutOfRangeWhenCalculatingException);

	numbers = { 0, 2147483647 };
	REQUIRE(GetSumm(numbers) == 2147483647);

	numbers = { -1, -2147483647 };
	REQUIRE_THROWS_AS(GetSumm(numbers), ValueOutOfRangeWhenCalculatingException);

	numbers = { 0, -2147483647 };
	REQUIRE(GetSumm(numbers) == -2147483647);
}

TEST_CASE("TestGetComposition")
{
	std::vector<int> numbers = { 5, 5, 5 };

	REQUIRE(GetComposition(numbers) == 125);

	numbers = {};
	REQUIRE(GetComposition(numbers) == 1);

	numbers = { -2, -3 };
	REQUIRE(GetComposition(numbers) == 6);

	numbers = { -2, 2 };
	REQUIRE(GetComposition(numbers) == -4);

	numbers = { 2, 2147483647 };
	REQUIRE_THROWS_AS(GetComposition(numbers), ValueOutOfRangeWhenCalculatingException);

	numbers = { -2, -2147483647 };
	REQUIRE_THROWS_AS(GetComposition(numbers), ValueOutOfRangeWhenCalculatingException);

	numbers = { 2, -2147483647 };
	REQUIRE_THROWS_AS(GetComposition(numbers), ValueOutOfRangeWhenCalculatingException);

	numbers = { -2, 2147483647 };
	REQUIRE_THROWS_AS(GetComposition(numbers), ValueOutOfRangeWhenCalculatingException);

	numbers = { 1, 2147483647 };
	REQUIRE(GetComposition(numbers) == 2147483647);

	numbers = { 1, -2147483647 };
	REQUIRE(GetComposition(numbers) == -2147483647);
}

TEST_CASE("TestCalculate")
{
	std::vector<int> numbers = { 5, 5, 5 };

	REQUIRE(Calculate(numbers, Operation::PLUS) == 15);
	REQUIRE(Calculate(numbers, Operation::MULTIPLY) == 125);

	numbers = {};
	REQUIRE(Calculate(numbers, Operation::PLUS) == 0); // TODO: Подумать над исключением
	REQUIRE(Calculate(numbers, Operation::MULTIPLY) == 1);
}

TEST_CASE("TestCalculateExpressionInStack")
{
	std::stack<Element> stack;

	REQUIRE_THROWS_AS(CalculateExpressionInStack(stack), InvalidExpressionException);

	stack.push(CreateOpenBracketElement());
	REQUIRE_THROWS_AS(CalculateExpressionInStack(stack), InvalidExpressionException);

	stack.push(CreateOpenBracketElement());
	stack.push(CreateElement(5));
	REQUIRE(CalculateExpressionInStack(stack) == 5);
	REQUIRE(stack.size() == 0);

	stack.push(CreateOpenBracketElement());
	stack.push(CreateElement(Operation::PLUS));
	stack.push(CreateElement(5));
	REQUIRE(CalculateExpressionInStack(stack) == 5);
	REQUIRE(stack.size() == 0);

	stack.push(CreateOpenBracketElement());
	stack.push(CreateElement(Operation::MULTIPLY));
	stack.push(CreateElement(5));
	REQUIRE(CalculateExpressionInStack(stack) == 5);
	REQUIRE(stack.size() == 0);

	stack.push(CreateOpenBracketElement());
	stack.push(CreateElement(Operation::MULTIPLY));
	stack.push(CreateElement(5));
	stack.push(CreateElement(6));
	REQUIRE(CalculateExpressionInStack(stack) == 30);
	REQUIRE(stack.size() == 0);

	stack.push(CreateOpenBracketElement());
	stack.push(CreateElement(Operation::PLUS));
	stack.push(CreateElement(5));
	stack.push(CreateElement(6));
	REQUIRE(CalculateExpressionInStack(stack) == 11);
	REQUIRE(stack.size() == 0);

	stack.push(CreateElement(5));
	stack.push(CreateOpenBracketElement());
	REQUIRE_THROWS_AS(CalculateExpressionInStack(stack), InvalidExpressionException);
}

TEST_CASE("TestGetElement")
{
	std::istringstream input;

	REQUIRE_THROWS_AS(GetElement(input), InvalidExpressionException);

	input.clear();
	input.str("(");
	REQUIRE(GetElement(input).type == ElementType::OPEN_BRACKET);

	input.clear();
	input.str("999)");
	Element element = GetElement(input);
	REQUIRE(element.type == ElementType::VALUE);
	REQUIRE(element.data.value == 999);
	REQUIRE(GetElement(input).type == ElementType::CLOSE_BRACKET);

	input.clear();
	input.str("-77");
	element = GetElement(input);
	REQUIRE(element.type == ElementType::VALUE);
	REQUIRE(element.data.value == -77);

	input.clear();
	input.str("2147483647");
	element = GetElement(input);
	REQUIRE(element.type == ElementType::VALUE);
	REQUIRE(element.data.value == 2147483647);

	input.clear();
	input.str("2147483648");
	REQUIRE_THROWS_AS(GetElement(input), ValueOutOfRangeException);

	input.clear();
	input.str("-2147483647");
	element = GetElement(input);
	REQUIRE(element.type == ElementType::VALUE);
	REQUIRE(element.data.value == -2147483647);

	input.clear();
	input.str("-2147483648");
	REQUIRE_THROWS_AS(GetElement(input), ValueOutOfRangeException);

	input.clear();
	input.str("*");
	element = GetElement(input);
	REQUIRE(element.type == ElementType::OPERATION);
	REQUIRE(element.data.operation == Operation::MULTIPLY);

	input.clear();
	input.str("+");
	element = GetElement(input);
	REQUIRE(element.type == ElementType::OPERATION);
	REQUIRE(element.data.operation == Operation::PLUS);

	input.clear();
	input.str("&");
	REQUIRE_THROWS_AS(GetElement(input), InvalidSymbolInExpressionException);
}