#include "./Exception/InvalidPortException.h"
#include "./Exception/InvalidProtocolException.h"
#include "./Exception/InvalidURLException.h"
#include "./Exception/PortOutOfRangeException.h"
#include <string>

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443,
	FTP = 21,
	UNKNOWN = 0,
};

Protocol ConvertStringToProtocol(const std::string& string);

void ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
