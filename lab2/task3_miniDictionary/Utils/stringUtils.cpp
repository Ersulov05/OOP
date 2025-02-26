#include "stringUtils.h"

wchar_t toLower(const wchar_t& symbol)
{
	std::locale loc("");
	return std::tolower(symbol, loc);
}

void AssertStringConversionIsSuccessful(const size_t result)
{
	if (result == static_cast<size_t>(-1))
	{
		throw InvalidConvertationStringException();
	}
}

std::wstring Utf8ToWstring(const std::string& str)
{
	std::vector<wchar_t> wbuffer(str.size() + 1);
	std::mbstate_t state = std::mbstate_t();
	const char* src = str.c_str();
	size_t result = std::mbsrtowcs(wbuffer.data(), &src, wbuffer.size(), &state);
	AssertStringConversionIsSuccessful(result);
	return std::wstring(wbuffer.data());
}

std::string WstringToUtf8(const std::wstring& wstr)
{
	std::vector<char> buffer(wstr.size() * 4 + 1);
	std::mbstate_t state = std::mbstate_t();
	const wchar_t* wsrc = wstr.c_str();
	size_t result = std::wcsrtombs(buffer.data(), &wsrc, buffer.size(), &state);
	AssertStringConversionIsSuccessful(result);
	return std::string(buffer.data());
}

std::string GetLowerCase(const std::string& string)
{
	std::wstring wstr = Utf8ToWstring(string);

	std::wstring lowerCaseWstr;
	for (wchar_t ch : wstr)
	{
		lowerCaseWstr += toLower(ch);
	}

	return WstringToUtf8(lowerCaseWstr);
}

std::string GetTrimmedString(const std::string& string)
{
	size_t start = string.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
	{
		return "";
	}
	size_t end = string.find_last_not_of(" \t\r\n");
	return string.substr(start, end - start + 1);
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

std::string GetEscapedString(const std::string& string, const std::string& escapeSymbol)
{
	return ReplaceLine(string, escapeSymbol, "\\" + escapeSymbol);
}

std::string GetUnescapedString(const std::string& string, const std::string& escapeSymbol)
{
	return ReplaceLine(string, "\\" + escapeSymbol, escapeSymbol);
}