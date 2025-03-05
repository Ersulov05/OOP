#pragma once
#include "../Exception/InvalidConvertationStringException.h"
#include <string>
#include <vector>

std::string GetLowerCase(const std::string& string);
std::string GetTrimmedString(const std::string& string);
std::string ReplaceLine(const std::string& string,
	const std::string& searchString,
	const std::string& replaceString);
std::string GetEscapedString(const std::string& string, const std::string& escapeSymbol);
std::string GetUnescapedString(const std::string& string, const std::string& escapeSymbol);