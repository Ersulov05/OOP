#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Utils/Element.h"

TEST_CASE("TestCreateBracketElement")
{
	REQUIRE(CreateOpenBracketElement().type == ElementType::OPEN_BRACKET);
	REQUIRE(CreateCloseBracketElement().type == ElementType::CLOSE_BRACKET);
}

TEST_CASE("TestCreateElement")
{
	Element element;
	element = CreateElement(45);
	REQUIRE(element.type == ElementType::VALUE);
	REQUIRE(element.data.value == 45);

	element = CreateElement(-45);
	REQUIRE(element.type == ElementType::VALUE);
	REQUIRE(element.data.value == -45);

	element = CreateElement(Operation::PLUS);
	REQUIRE(element.type == ElementType::OPERATION);
	REQUIRE(element.data.operation == Operation::PLUS);

	element = CreateElement(Operation::MULTIPLY);
	REQUIRE(element.type == ElementType::OPERATION);
	REQUIRE(element.data.operation == Operation::MULTIPLY);
}

TEST_CASE("TestCharToElement")
{
	Element element;
	element = CharToElement('*');
	REQUIRE(element.type == ElementType::OPERATION);
	REQUIRE(element.data.operation == Operation::MULTIPLY);

	element = CharToElement('+');
	REQUIRE(element.type == ElementType::OPERATION);
	REQUIRE(element.data.operation == Operation::PLUS);

	element = CharToElement(')');
	REQUIRE(element.type == ElementType::CLOSE_BRACKET);

	element = CharToElement('(');
	REQUIRE(element.type == ElementType::OPEN_BRACKET);

	REQUIRE_THROWS_AS(CharToElement('&'), InvalidSymbolInExpressionException);
}