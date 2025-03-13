#include "ParseURL.h"
#include "Utils/StringUtils.h"
#include <regex>

const int MAX_PORT = 65535;
const int MIN_PORT = 1;

Protocol ConvertStringToProtocol(const std::string& string)
{
	std::string lowerCaseString = GetLowerCase(string);

	if (lowerCaseString == "http")
	{
		return Protocol::HTTP;
	}
	else if (lowerCaseString == "https")
	{
		return Protocol::HTTPS;
	}
	else if (lowerCaseString == "ftp")
	{
		return Protocol::FTP;
	}
	else
	{
		throw InvalidProtocolException(string);
	}
}

void AssertPortNotOutOfRange(int port)
{
	if (port < 1 || port > MAX_PORT)
	{
		throw PortOutOfRangeException(MIN_PORT, MAX_PORT);
	}
}

int ConvertStringToPort(const std::string& string, Protocol protocol)
{
	if (string == "")
	{
		return static_cast<int>(protocol);
	}

	int port = 0;
	try
	{
		port = std::stoi(string);
	}
	catch (const std::invalid_argument& e)
	{
		throw InvalidPortException(string);
	}
	catch (const std::out_of_range& e)
	{
		throw PortOutOfRangeException(MIN_PORT, MAX_PORT);
	}
	AssertPortNotOutOfRange(port);

	return port;
}

void ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlRegex(R"(^(.+)://([^/:]+)(?::([^/]*))?(/.*)?$)"); // TODO: http https ftp //выяснить что значат ::
	std::smatch match;

	if (!std::regex_match(url, match, urlRegex))
	{
		throw InvalidURLException(url);
	}

	std::string protocolString = match[1].str();
	host = match[2].str();
	std::string portString = match[3].str();
	document = match[4].str();
	if (!document.empty())
	{
		document = document.substr(1);
	}

	protocol = ConvertStringToProtocol(protocolString);
	port = ConvertStringToPort(portString, protocol);
}