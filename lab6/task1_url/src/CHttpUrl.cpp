#include "./CHttpUrl.h"
#include "../Utils/StringUtils.h"
#include "./Exception/CUrlParsingError.h"
#include "./Exception/InvalidDomainException.h"
#include "./Exception/InvalidPortException.h"
#include "./Exception/InvalidProtocolException.h"
#include "./Exception/PortOutOfRangeException.h"
#include <regex>

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::regex urlRegex(R"(^(http|https)://([^/:]+)(?::([^/]*))?(/.*)?$)", std::regex_constants::icase);
	std::smatch match;

	if (!std::regex_match(url, match, urlRegex))
	{
		throw CUrlParsingError();
	}

	std::string protocolString = match[1].str();
	m_domain = match[2].str();
	std::string portString = match[3].str();
	m_document = match[4].str();
	m_protocol = ConvertStringToProtocol(protocolString);
	m_port = portString == ""
		? static_cast<unsigned short>(m_protocol)
		: ConvertStringToPort(portString);
	CorrectDocumentPath();
}

CHttpUrl& CHttpUrl::operator=(const CHttpUrl& other)
{
	if (this != &other)
	{
		m_protocol = other.m_protocol;
		m_domain = other.m_domain;
		m_port = other.m_port;
		m_document = other.m_document;
	}
	return *this;
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol)
	: m_protocol(protocol)
	, m_domain(domain)
	, m_port(static_cast<unsigned short>(protocol))
	, m_document(document)
{
	AssertValidDomain(m_domain);
	CorrectDocumentPath();
}

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
	: m_protocol(protocol)
	, m_domain(domain)
	, m_port(port)
	, m_document(document)
{
	AssertValidPort(m_port);
	AssertValidDomain(m_domain);
	CorrectDocumentPath();
}

std::string CHttpUrl::GetURL() const
{
	return static_cast<unsigned short>(m_protocol) == m_port
		? ConvertProtocolToString(m_protocol) + "://" + m_domain + m_document
		: ConvertProtocolToString(m_protocol) + "://" + m_domain + ":" + std::to_string(m_port) + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

Protocol CHttpUrl::ConvertStringToProtocol(const std::string& string) const
{
	std::string lowerCaseString = GetLowerCase(string);
	auto it = STRING_TO_PROTOCOL_MAP.find(lowerCaseString);
	if (it != STRING_TO_PROTOCOL_MAP.end())
	{
		return it->second;
	}
	throw InvalidProtocolException(string);
}

std::string CHttpUrl::ConvertProtocolToString(const Protocol protocol) const
{
	auto it = PROTOCOL_TO_STRING_MAP.find(protocol);
	if (it != PROTOCOL_TO_STRING_MAP.end())
	{
		return it->second;
	}
	throw InvalidProtocolException("");
}

unsigned short CHttpUrl::ConvertStringToPort(const std::string& string) const
{
	unsigned long port = 0;
	try
	{
		port = std::stoul(string);
	}
	catch (const std::invalid_argument& e)
	{
		throw InvalidPortException(string);
	}
	catch (const std::out_of_range& e)
	{
		throw PortOutOfRangeException(MIN_PORT, MAX_PORT);
	}
	AssertValidPort(port);

	return static_cast<unsigned short>(port);
}

void CHttpUrl::AssertValidPort(unsigned long port) const
{
	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw PortOutOfRangeException(MIN_PORT, MAX_PORT);
	}
}

void CHttpUrl::AssertValidDomain(const std::string& domain) const
{
	if (domain.empty() || !std::regex_match(domain, DOMAIN_REGEX))
	{
		throw InvalidDomainException(domain);
	}
}

void CHttpUrl::CorrectDocumentPath()
{
	if (m_document.empty() || m_document[0] != '/')
	{
		m_document = "/" + m_document;
	}
}