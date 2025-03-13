#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../ParseURL.h"

struct URL
{
	std::string url;
	Protocol protocol = Protocol::UNKNOWN;
	int port = 0;
	std::string host;
	std::string document;

	friend bool operator==(const URL& lhs, const URL& rhs)
	{
		return lhs.url == rhs.url && lhs.protocol == rhs.protocol && lhs.port == rhs.port && lhs.host == rhs.host && lhs.document == rhs.document;
	}
};

TEST_CASE("test ParseURL")
{
	std::vector<URL> testsData = {
		{ "Http://ersulov.ru/index.php", Protocol::HTTP, 80, "ersulov.ru", "index.php" },
		{ "FTP://ersulov.ru/index.php", Protocol::FTP, 21, "ersulov.ru", "index.php" },
		{ "htTps://ersulov.ru", Protocol::HTTPS, 443, "ersulov.ru", "" },
		{ "https://ersulov.ru:8080", Protocol::HTTPS, 8080, "ersulov.ru", "" },
		{ "HttP://ersulov.ru:1/index.php", Protocol::HTTP, 1, "ersulov.ru", "index.php" },
		{ "HTTPS://ersulov.ru:65535/lab1/document/index.php", Protocol::HTTPS, 65535, "ersulov.ru", "lab1/document/index.php" },
		// TODO проверить query параметр
	};

	URL url;
	for (const URL& testData : testsData)
	{
		url.url = testData.url;
		ParseURL(testData.url, url.protocol, url.port, url.host, url.document);
		REQUIRE(url == testData);
	}
}

TEST_CASE("test ParseURL Failed")
{
	Protocol protocol = Protocol::UNKNOWN;
	int port = 0;
	std::string host;
	std::string document;

	std::string url = "";
	REQUIRE_THROWS_AS(ParseURL(url, protocol, port, host, document), InvalidURLException);

	url = "http://";
	REQUIRE_THROWS_AS(ParseURL(url, protocol, port, host, document), InvalidURLException);

	url = "http//ersulov.ru";
	REQUIRE_THROWS_AS(ParseURL(url, protocol, port, host, document), InvalidURLException);

	url = "http:ersulov.ru";
	REQUIRE_THROWS_AS(ParseURL(url, protocol, port, host, document), InvalidURLException);

	url = "error://ersulov.ru/index.php";
	REQUIRE_THROWS_AS(ParseURL(url, protocol, port, host, document), InvalidProtocolException);

	url = "http://ersulov.ru:ab/index.php";
	REQUIRE_THROWS_AS(ParseURL(url, protocol, port, host, document), InvalidPortException);

	url = "http://ersulov.ru:0/index.php";
	REQUIRE_THROWS_AS(ParseURL(url, protocol, port, host, document), PortOutOfRangeException);

	url = "http://ersulov.ru:65536/index.php";
	REQUIRE_THROWS_AS(ParseURL(url, protocol, port, host, document), PortOutOfRangeException);
}