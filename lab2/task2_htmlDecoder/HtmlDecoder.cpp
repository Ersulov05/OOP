#include "HtmlDecoder.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <optional>

const char BEGIN_SYMBOL_OF_CODE = '&';
const std::string END_SYMBOL_OF_CODE = ";";

const std::map<std::string, std::string> ENTRY_MAP = {
	{ "&quot;", "\"" },
	{ "&apos;", "\'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

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
	size_t positionOfBeginSymbolOfCode = 0; // стоит убрать Of
	size_t positionOfEndSymbolOfCode = 0;
	std::string result;
	while ((positionOfEndSymbolOfCode = string.find(END_SYMBOL_OF_CODE, pos)) != std::string::npos)
	{
		positionOfBeginSymbolOfCode = string.rfind(BEGIN_SYMBOL_OF_CODE, positionOfEndSymbolOfCode);
		if (positionOfBeginSymbolOfCode == std::string::npos || positionOfBeginSymbolOfCode < pos)
		{
			result.append(string, pos, positionOfEndSymbolOfCode - pos + 1);
		}
		else
		{
			result.append(string, pos, positionOfBeginSymbolOfCode - pos);
			std::string htmlCode = string.substr(positionOfBeginSymbolOfCode, positionOfEndSymbolOfCode - positionOfBeginSymbolOfCode + 1);
			result += GetHTMLDecode(htmlCode);
		}

		pos = positionOfEndSymbolOfCode + 1;
	}
	result.append(string, pos, string.length() - pos);
	return result;
}