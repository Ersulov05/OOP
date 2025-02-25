// Ерсулов Андрей ПС-21, лабораторная №1
// Среда Visual Studio Code
// Компилятор g++ c++20

#include "Exception/FailedOpenFileException.h"
#include "Exception/InputOutputFileNameMatchException.h"
#include "Exception/InvalidArgumentCountException.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <optional>

const int EXPECTED_ARG_COUNT = 3;
const char BEGIN_SYMBOL_OF_CODE = '&';
const char END_SYMBOL_OF_CODE = ';';

const std::map<std::string, std::string> ENTRY_MAP = {
	{ "&quot;", "\"" },
	{ "&apos;", "\'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

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

std::string GetHTMLDecode(const std::string& string)
{
	auto iterator = ENTRY_MAP.find(string);
	if (iterator != ENTRY_MAP.end())
	{
		return iterator->second;
	}
	return string;
}

std::string ReplaceLine(const std::string& string,
	const std::string& searchString,
	const std::string& replaceString)
{
	size_t pos = 0;
	size_t foundPos = 0;
	std::string result;
	while ((foundPos = string.find(searchString, pos)) != std::string::npos)
	{
		result.append(string, pos, foundPos - pos);
		result.append(replaceString);

		pos = foundPos + searchString.length();
	}
	result.append(string, pos, string.length() - pos);

	return result;
}

std::string DecodeHTMLString(const std::string& string)
{
	size_t pos = 0;
	size_t positionOfBeginSymbolOfCode = 0;
	size_t positionOfEndSymbolOfCode = 0;
	std::string result;
	while ((positionOfEndSymbolOfCode = string.find(END_SYMBOL_OF_CODE, pos)) != std::string::npos)
	{
		positionOfBeginSymbolOfCode = string.rfind(BEGIN_SYMBOL_OF_CODE, positionOfEndSymbolOfCode);
		if (positionOfBeginSymbolOfCode == std::string::npos)
		{
			result.append(string, pos, positionOfEndSymbolOfCode - pos + 1);
		}
		else
		{
			result.append(string, pos, positionOfBeginSymbolOfCode - pos);
			std::string htmlCode = string.substr(positionOfBeginSymbolOfCode, positionOfEndSymbolOfCode - positionOfBeginSymbolOfCode + 1);
			result.append(GetHTMLDecode(htmlCode));
		}

		pos = positionOfEndSymbolOfCode + 1;
	}
	result.append(string, pos, string.length() - pos);
	return result;
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