#include "Exception/FailedOpenFileException.h"
#include "Exception/InputOutputFileNameMatchException.h"
#include "Exception/InvalidArgumentCountException.h"
#include "HtmlDecoder.h"

#include <fstream>
#include <iostream>
#include <optional>

const int EXPECTED_ARG_COUNT = 3;

struct Arg
{
	bool isCrypt = false;
	std::string outputFileName;
	std::string inputFileName;
	u_int8_t key = 0;
};

void AssertInputOutputFileNameMismatch(const std::string& inputFileName, const std::string& outputFileName)
{
	if (inputFileName == outputFileName)
	{
		throw InputOutputFileNameMatchException();
	}
}

void AssertExpectedArgumentCount(int argc)
{
	if (argc != EXPECTED_ARG_COUNT)
	{
		throw InvalidArgumentCountException();
	}
}

std::optional<Arg> ParseArgs(int argc, char* argv[])
{
	if (argc == 1)
	{
		return std::nullopt;
	}
	AssertExpectedArgumentCount(argc);
	AssertInputOutputFileNameMismatch(argv[1], argv[2]);

	Arg arg;
	arg.inputFileName = argv[1];
	arg.outputFileName = argv[2];

	return arg;
}

void DecodeHTML(std::istream& input, std::ostream& output)
{
	std::string line;

	while (getline(input, line))
	{
		output << DecodeHTMLString(line) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		std::optional<Arg> arg = ParseArgs(argc, argv);
		if (arg)
		{
			std::ifstream inputFile(arg->inputFileName);
			std::ofstream outputFile(arg->outputFileName);
			if (!inputFile.is_open())
			{
				throw FailedOpenFileException();
			}
			if (!outputFile.is_open())
			{
				throw FailedOpenFileException();
			}
			DecodeHTML(inputFile, outputFile);
			inputFile.close();
			outputFile.close();
		}
		else
		{
			DecodeHTML(std::cin, std::cout);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}