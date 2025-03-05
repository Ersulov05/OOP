#include "Exception/FailedOpenFileException.h"
#include "Exception/InputOutputFileNameMatchException.h"
#include "Exception/InvalidArgumentCountException.h"
#include "MiniDictionary.h"
#include "Utils/StringUtils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>

const int EXPECTED_ARG_COUNT = 2;
const std::string QUIT_STRING = "...";
const std::string CONSOLE_SYMBOL = ">";
const std::string TRANSLATIONS_SEPARATOR = ", ";

std::string GetExpression()
{
	std::cout << CONSOLE_SYMBOL;
	std::string line;
	getline(std::cin, line);
	return line;
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

bool AreCorrectExpression(const std::string& expression)
{
	return !(GetTrimmedString(expression).empty());
}

bool RequestTranslationProcess(std::ostream& output, Dictionary& dictionary, const std::string& expression)
{
	std::string translation = RequestTranslation(expression);
	if (translation.empty())
	{
		output << "Слово “" << expression << "” проигнорировано.\n";
		return false;
	}

	if (!AreCorrectExpression(translation))
	{
		std::cout << "Некорректное выражение" << std::endl;
		return false;
	}

	AddTranslationInDictionary(dictionary, expression, translation);
	AddTranslationInDictionary(dictionary, translation, expression);
	output << "Слово “" << expression << "” сохранено в словаре как “" << translation << "”.\n";
	return true;
}

bool WorkWithDictionary(Dictionary& dictionary)
{
	std::string expression;
	std::set<std::string> translations;
	bool isChangedDictionary = false;
	while (true)
	{
		expression = GetExpression();
		if (expression == QUIT_STRING)
		{
			break;
		}

		if (!AreCorrectExpression(expression))
		{
			std::cout << "Некорректное выражение" << std::endl;
			continue;
		}

		translations = GetTranslationFromDictionary(dictionary, expression);
		if (!translations.empty())
		{
			PrintTranslations(std::cout, translations, TRANSLATIONS_SEPARATOR);
			std::cout << std::endl;
			continue;
		}
		isChangedDictionary = RequestTranslationProcess(std::cout, dictionary, expression);
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
	try
	{
		Arg arg = ParseArgs(argc, argv);
		Dictionary dictionary;
		LoadDictionary(arg.fileName, dictionary);
		if (WorkWithDictionary(dictionary) && RequestSaveDictionary())
		{
			SaveDictionary(arg.fileName, dictionary);
			std::cout << "Изменения сохранены. ";
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