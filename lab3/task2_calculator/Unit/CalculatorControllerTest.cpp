#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Controller/CalculatorController.h"
#include "../Controller/Exception/InvalidCalculatorCommandArgumentsException.h"
#include <sstream>

TEST_CASE("TestHandleCalculatorCommandVAR")
{
	CalculatorController calculatorController;

	std::stringstream output;
	CalculatorCommand calculatorCommand(CalculatorCommandType::VAR, "x");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);

	calculatorCommand = CalculatorCommand(CalculatorCommandType::PRINT, "x");
	output.str("");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "x:nan\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::VAR, "b&b");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::VAR, "100x");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::VAR, "123.0.0");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::VAR, "");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");
}

TEST_CASE("TestHandleCalculatorCommandLET")
{
	CalculatorController calculatorController;

	std::stringstream output;
	CalculatorCommand calculatorCommand(CalculatorCommandType::LET, "x = 7");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);

	calculatorCommand = CalculatorCommand(CalculatorCommandType::PRINT, "x");
	output.str("");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "x:7.00\n");

	calculatorCommand = CalculatorCommand(CalculatorCommandType::LET, "y = x");
	output.str("");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);

	calculatorCommand = CalculatorCommand(CalculatorCommandType::PRINT, "y");
	output.str("");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "y:7.00\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::LET, "c=b&b");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::LET, "c=100x");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::LET, "c=123.0.0");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::LET, "");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");
}

TEST_CASE("TestHandleCalculatorCommandFN")
{
	CalculatorController calculatorController;

	std::stringstream output;
	CalculatorCommand calculatorCommand(CalculatorCommandType::LET, "x = 7");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);

	calculatorCommand = CalculatorCommand(CalculatorCommandType::FN, "y = x + x");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	calculatorCommand = CalculatorCommand(CalculatorCommandType::FN, "a = y * y");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	calculatorCommand = CalculatorCommand(CalculatorCommandType::FN, "  b   =   a   /   a  ");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	calculatorCommand = CalculatorCommand(CalculatorCommandType::FN, "c=b-b");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);

	calculatorCommand = CalculatorCommand(CalculatorCommandType::PRINTFNS);
	output.str("");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "a:196.00\nb:1.00\nc:0.00\ny:14.00\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::FN, "c=b&b");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::FN, "c=100");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::FN, "c=123hs");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");

	output.str("");
	calculatorCommand = CalculatorCommand(CalculatorCommandType::FN, "");
	calculatorController.HandleCalculatorCommand(output, calculatorCommand);
	REQUIRE(output.str() == "Invalid calculator command arguments\n");
}