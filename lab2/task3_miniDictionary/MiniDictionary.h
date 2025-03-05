#pragma once
#include "Exception/FailedOpenFileException.h"
#include "Exception/IncorrectExpressionException.h"
#include "Utils/StringUtils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>

using Dictionary = std::map<std::string, std::set<std::string>>;

const std::string ESCAPE_SYMBOL = "|";
const std::string DIVIDING_DICTIONARY_STRING = " " + ESCAPE_SYMBOL + " ";

void AddTranslationInDictionary(Dictionary& dictionary, const std::string& key, const std::string& value);

void LoadDictionary(const std::string& inputFileName, Dictionary& dictionary);

void SaveDictionary(const std::string& outputFileName, const Dictionary& dictionary);

std::set<std::string> GetTranslationFromDictionary(const Dictionary& dictionary, const std::string& expression);

void PrintTranslations(std::ostream& output, const std::set<std::string>& translations, const std::string& separator);