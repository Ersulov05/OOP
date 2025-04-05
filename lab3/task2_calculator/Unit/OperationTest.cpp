#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Calculator/Entity/Operation.h"

TEST_CASE("TestCreateOperation")
{
	Operation operation = GetOperationByString("+");
	REQUIRE(operation == Operation::PLUS);

	operation = GetOperationByString("-");
	REQUIRE(operation == Operation::MINUS);

	operation = GetOperationByString("/");
	REQUIRE(operation == Operation::DIVIDING);

	operation = GetOperationByString("*");
	REQUIRE(operation == Operation::MULTIPLY);

	operation = GetOperationByString("%");
	REQUIRE(operation == Operation::NONE);

	operation = GetOperationByString("");
	REQUIRE(operation == Operation::NONE);
}

TEST_CASE("TestExecuteOperation")
{
	double value = ExecuteOperation(Operation::PLUS, 5, 5);
	REQUIRE(value == 10);

	value = ExecuteOperation(Operation::MULTIPLY, 5, 5);
	REQUIRE(value == 25);

	value = ExecuteOperation(Operation::DIVIDING, 5, 5);
	REQUIRE(value == 1);

	value = ExecuteOperation(Operation::MINUS, 5, 5);
	REQUIRE(value == 0);

	value = ExecuteOperation(Operation::DIVIDING, 5, 0);
	REQUIRE(std::isnan(value));

	value = ExecuteOperation(Operation::PLUS, 5, NAN);
	REQUIRE(std::isnan(value));

	value = ExecuteOperation(Operation::MULTIPLY, 5, NAN);
	REQUIRE(std::isnan(value));

	value = ExecuteOperation(Operation::DIVIDING, 5, NAN);
	REQUIRE(std::isnan(value));

	value = ExecuteOperation(Operation::MINUS, 5, NAN);
	REQUIRE(std::isnan(value));

	value = ExecuteOperation(Operation::NONE, 5, 5);
	REQUIRE(std::isnan(value));
}