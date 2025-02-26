#include "Exception/FailedOpenFileException.h"
#include "Exception/InputOutputFileNameMatchException.h"
#include "Exception/InvalidArgumentCountException.h"
#include "Utils/stringUtils.h"
#include <fstream>
#include <iostream>
#include <map>

const int EXPECTED_ARG_COUNT = 2;
const std::string QUIT_STRING = "...";
const std::string ESCAPE_SYMBOL = "|";
const std::string DIVIDING_DICTIONARY_STRING = " " + ESCAPE_SYMBOL + " ";
const std::string CONSOLE_SYMBOL = ">";

void LoadDictionary(const std::string& inputFileName, std::map<std::string, std::string>& dictionary)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		throw FailedOpenFileException();
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		size_t pos = line.find(DIVIDING_DICTIONARY_STRING);
		if (pos != std::string::npos)
		{
			std::string key = line.substr(0, pos);
			std::string value = line.substr(pos + DIVIDING_DICTIONARY_STRING.size());

			key = GetUnescapedString(GetLowerCase(GetTrimmedString(key)), ESCAPE_SYMBOL);
			value = GetUnescapedString(GetTrimmedString(value), ESCAPE_SYMBOL);

			dictionary[key] = value;
		}
	}

	inputFile.close();
}

void SaveDictionary(const std::string& outputFileName, const std::map<std::string, std::string>& dictionary)
{
	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		throw FailedOpenFileException();
	}

	for (const auto& [key, value] : dictionary)
	{
		outputFile << GetEscapedString(key, ESCAPE_SYMBOL) << DIVIDING_DICTIONARY_STRING << GetEscapedString(value, ESCAPE_SYMBOL) << std::endl;
	}
	outputFile.close();
	std::cout << "Изменения сохранены. ";
}

std::string GetExpression()
{
	std::cout << CONSOLE_SYMBOL;
	std::string line;
	getline(std::cin, line);
	return line;
}

std::string GetTranslationExpressionFromDictionary(const std::map<std::string, std::string>& dictionary, const std::string& expression)
{
	auto it = dictionary.find(GetLowerCase(GetTrimmedString(expression)));
	if (it != dictionary.end())
	{
		return it->second;
	}
	return "";
}

bool RequestSaveDictionary()
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n" + CONSOLE_SYMBOL;
	std::string response;
	getline(std::cin, response);
	return response == "Y" || response == "y";
}

std::string RequestTranslation(const std::string& expression)
{
	std::cout << "Неизвестное слово “" << expression << "”. Введите перевод или пустую строку для отказа.\n" + CONSOLE_SYMBOL;
	std::string translatedExpression;
	getline(std::cin, translatedExpression);
	return translatedExpression;
}

void SaveTranslationInDictionary(std::map<std::string, std::string>& dictionary, const std::string& expression, const std::string& translatedExpression)
{
	dictionary[GetLowerCase(GetTrimmedString(expression))] = translatedExpression;
	std::cout << "Слово “" << expression << "” сохранено в словаре как “" << translatedExpression << "”.\n";
}

void PrintIgnoreSaveMessage(const std::string& expression)
{
	std::cout << "Слово “" << expression << "” проигнорировано.\n";
}

bool WorkWithDictionary(std::map<std::string, std::string>& dictionary)
{
	std::string string;
	std::string translation;
	bool isChangedDictionary = false;
	while (true)
	{
		string = GetExpression();
		if (string == QUIT_STRING)
		{
			break;
		}
		translation = GetTranslationExpressionFromDictionary(dictionary, string);
		if (translation.size() > 0)
		{
			std::cout << translation << std::endl;
		}
		else
		{
			translation = RequestTranslation(string);
			if (translation.size() > 0)
			{
				SaveTranslationInDictionary(dictionary, string, translation);
				isChangedDictionary = true;
			}
			else
			{
				PrintIgnoreSaveMessage(string);
			}
		}
	}
	return isChangedDictionary;
}

struct Arg
{
	std::string fileName;
};

void AssertCorrectFileName(const std::string& inputFileName)
{
	if (inputFileName == "")
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

Arg ParseArgs(int argc, char* argv[])
{
	AssertExpectedArgumentCount(argc);
	AssertCorrectFileName(argv[1]);

	Arg arg;
	arg.fileName = argv[1];

	return arg;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	try
	{
		Arg arg = ParseArgs(argc, argv);
		std::map<std::string, std::string> dictionary;
		LoadDictionary(arg.fileName, dictionary);
		if (WorkWithDictionary(dictionary) && RequestSaveDictionary())
		{
			SaveDictionary(arg.fileName, dictionary);
		}
		std::cout << "До свидания.\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}