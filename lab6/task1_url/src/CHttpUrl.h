#include <map>
#include <regex>
#include <string>

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
	std::string GetURLInfo() const;

	CHttpUrl& operator=(const CHttpUrl&);

	static std::string ConvertProtocolToString(const Protocol protocol);

private:
	const unsigned short MAX_PORT = 65535;
	const unsigned short MIN_PORT = 1;
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;

	inline static const std::map<std::string, Protocol> STRING_TO_PROTOCOL_MAP = {
		{ "http", Protocol::HTTP },
		{ "https", Protocol::HTTPS }
	};

	inline static const std::map<Protocol, std::string> PROTOCOL_TO_STRING_MAP = {
		{ Protocol::HTTP, "http" },
		{ Protocol::HTTPS, "https" }
	};

	Protocol ConvertStringToProtocol(const std::string& string) const;
	unsigned short ConvertStringToPort(const std::string& string) const;
	void CorrectDocumentPath();
	void AssertValidPort(unsigned long port) const;
	void AssertValidDomain(const std::string& domain) const;
};
