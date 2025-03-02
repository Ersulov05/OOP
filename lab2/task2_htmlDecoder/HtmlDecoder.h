#include <iostream>
#include <limits>
#include <map>
#include <optional>

std::string GetHTMLDecode(const std::string& string);

std::string ReplaceLine(const std::string& string,
	const std::string& searchString,
	const std::string& replaceString);

std::string DecodeHTMLString(const std::string& string);