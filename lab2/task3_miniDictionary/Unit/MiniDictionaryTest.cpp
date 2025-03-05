#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../MiniDictionary.h"
#include <sstream>

TEST_CASE("AddExpressionWithTranslationInDictionarySuccess")
{
	Dictionary dictionary;
	AddTranslationInDictionary(dictionary, "hello", "привет");
	REQUIRE(dictionary.size() == 1);

	AddTranslationInDictionary(dictionary, "hello", "приветик");
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary["hello"].size() == 2);

	AddTranslationInDictionary(dictionary, "hEllO", "здравствуйте");
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary["hello"].size() == 3);

	AddTranslationInDictionary(dictionary, "HELLO", "здравствуйте");
	REQUIRE(dictionary.size() == 1);
	REQUIRE(dictionary["hello"].size() == 3);

	AddTranslationInDictionary(dictionary, "cat", "кот");
	REQUIRE(dictionary.size() == 2);

	AddTranslationInDictionary(dictionary, "DOG", "СоБаКа");
	REQUIRE(dictionary.size() == 3);
	REQUIRE(dictionary["dog"] == std::set<std::string>{ "СоБаКа" });
}

TEST_CASE("AddExpressionWithTranslationInDictionaryIncorrectExpressionFailed")
{
	Dictionary dictionary;
	REQUIRE_THROWS_AS(AddTranslationInDictionary(dictionary, "", "привет"), IncorrectExpressionException);
	REQUIRE_THROWS_AS(AddTranslationInDictionary(dictionary, "hello", ""), IncorrectExpressionException);
}

TEST_CASE("GetTranslationFromDictionarySuccess")
{
	Dictionary dictionary;
	AddTranslationInDictionary(dictionary, "hello", "приВет");
	AddTranslationInDictionary(dictionary, "hello", "приветик");

	std::set<std::string> translations = GetTranslationFromDictionary(dictionary, "hello");
	REQUIRE(translations.size() == 2);
	REQUIRE(translations == std::set<std::string>{ "приВет", "приветик" });
}

TEST_CASE("TestPrintTranslations")
{
	Dictionary dictionary;
	std::set<std::string> translations = { "приВет", "приветик" };
	std::stringstream output;

	std::string expectedOutput = "приВет, приветик";
	PrintTranslations(output, translations, ", ");
	REQUIRE(output.str() == expectedOutput);
	output.str("");

	translations = { "hello" };
	expectedOutput = "hello";
	PrintTranslations(output, translations, ", ");
	REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("SaveAndLoadDictionarySuccess")
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	Dictionary dictionary;
	std::string fileName = "test.txt";
	AddTranslationInDictionary(dictionary, "hello", "приВет");
	AddTranslationInDictionary(dictionary, "hello", "приветик");
	SaveDictionary(fileName, dictionary);
	Dictionary dictionary2;
	LoadDictionary(fileName, dictionary2);
	REQUIRE(dictionary2.size() == 3);
}