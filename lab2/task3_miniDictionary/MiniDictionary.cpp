#include "Exception/FailedOpenFileException.h"
#include "Exception/InputOutputFileNameMatchException.h"
#include "Exception/InvalidArgumentCountException.h"
#include "Utils/stringUtils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>

const int EXPECTED_ARG_COUNT = 2;
const std::string QUIT_STRING = "...";
const std::string ESCAPE_SYMBOL = "|";
const std::string DIVIDING_DICTIONARY_STRING = " " + ESCAPE_SYMBOL + " ";
const std::string CONSOLE_SYMBOL = ">";

using Dictionary = std::map<std::string, std::set<std::string>>;

void AddTranslationInDictionary(Dictionary& dictionary, const std::string& key, const std::string& value)
{
	std::string savedKey = GetLowerCase(GetTrimmedString(key));
	std::string savedValue = GetTrimmedString(value);
	if (dictionary.find(savedKey) != dictionary.end())
	{
		dictionary[savedKey].insert(savedValue);
	}
	else
	{
		dictionary[savedKey] = { savedValue };
	}
}

void LoadDictionary(const std::string& inputFileName, Dictionary& dictionary)
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

			key = GetUnescapedString(key, ESCAPE_SYMBOL);
			value = GetUnescapedString(value, ESCAPE_SYMBOL);

			AddTranslationInDictionary(dictionary, key, value);
			AddTranslationInDictionary(dictionary, value, key);
		}
	}

	inputFile.close();
}

void SaveDictionary(const std::string& outputFileName, const Dictionary& dictionary)
{
	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		throw FailedOpenFileException();
	}

	for (const auto& [key, values] : dictionary)
	{
		for (const auto& value : values)
		{
			outputFile << GetEscapedString(key, ESCAPE_SYMBOL) << DIVIDING_DICTIONARY_STRING << GetEscapedString(value, ESCAPE_SYMBOL) << std::endl;
		}
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

std::set<std::string> GetTranslationExpressionFromDictionary(const Dictionary& dictionary, const std::string& expression)
{
	auto it = dictionary.find(GetLowerCase(GetTrimmedString(expression)));
	if (it != dictionary.end())
	{
		return it->second;
	}
	return {};
}

bool RequestSaveDictionary()
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n" + CONSOLE_SYMBOL;
	std::string response;
	getline(std::cin, response);
	return response == "Y" || response == "y";
}

std::set<std::string> RequestTranslation(const std::string& expression)
{
	std::cout << "Неизвестное слово “" << expression << "”. Введите перевод или пустую строку для отказа.\n" + CONSOLE_SYMBOL;
	std::string translatedExpression;
	getline(std::cin, translatedExpression);
	return { translatedExpression };
}

void SaveTranslationInDictionary(Dictionary& dictionary, const std::string& expression, const std::string& translatedExpression)
{
	AddTranslationInDictionary(dictionary, expression, translatedExpression);
	AddTranslationInDictionary(dictionary, translatedExpression, expression);
	std::cout << "Слово “" << expression << "” сохранено в словаре как “" << translatedExpression << "”.\n";
}

void PrintIgnoreSaveMessage(const std::string& expression)
{
	std::cout << "Слово “" << expression << "” проигнорировано.\n";
}

void PrintTranslations(const std::set<std::string>& translations)
{
	size_t i = 0;
	for (const auto& translation : translations)
	{
		std::cout << translation;
		if (i < translations.size() - 1)
		{
			std::cout << ", ";
		}
		++i;
	}
	std::cout << std::endl;
}

bool WorkWithDictionary(Dictionary& dictionary)
{
	std::string string;
	std::set<std::string> translations;
	bool isChangedDictionary = false;
	while (true)
	{
		string = GetExpression();
		if (string == QUIT_STRING)
		{
			break;
		}

		translations = GetTranslationExpressionFromDictionary(dictionary, string);
		if (translations.size() > 0)
		{
			PrintTranslations(translations);
			continue;
		}

		translations = RequestTranslation(string);
		if (translations.size() > 0)
		{
			SaveTranslationInDictionary(dictionary, string, *translations.begin());
			isChangedDictionary = true;
			continue;
		}
		PrintIgnoreSaveMessage(string);
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
		Dictionary dictionary;
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