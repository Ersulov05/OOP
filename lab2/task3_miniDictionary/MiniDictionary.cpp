#include "MiniDictionary.h"

void AssertCorrectExpression(const std::string& expression)
{
	if (GetTrimmedString(expression).empty())
	{
		throw IncorrectExpressionException();
	}
}

void AddTranslationInDictionary(Dictionary& dictionary, const std::string& key, const std::string& value)
{
	AssertCorrectExpression(key);
	AssertCorrectExpression(value);
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
}

std::set<std::string> GetTranslationFromDictionary(const Dictionary& dictionary, const std::string& expression)
{
	auto it = dictionary.find(GetLowerCase(GetTrimmedString(expression)));
	if (it != dictionary.end())
	{
		return it->second;
	}
	return {};
}

void PrintTranslations(std::ostream& output, const std::set<std::string>& translations, const std::string& separator)
{
	size_t i = 0;
	for (const auto& translation : translations)
	{
		output << translation;
		if (i < translations.size() - 1)
		{
			output << separator;
		}
		++i;
	}
}