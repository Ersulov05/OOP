#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../src/CHttpUrl.h"
#include "../src/Exception/CUrlParsingError.h"
#include "../src/Exception/InvalidDomainException.h"
#include "../src/Exception/InvalidPortException.h"
#include "../src/Exception/PortOutOfRangeException.h"
#include <sstream>

TEST_CASE("test ParseURL")
{
	CHttpUrl url = CHttpUrl("Http://ersulov.ru/index.php");
	REQUIRE(url.GetURL() == "http://ersulov.ru/index.php");
	REQUIRE(url.GetPort() == 80);
	REQUIRE(url.GetDocument() == "/index.php");
	REQUIRE(url.GetDomain() == "ersulov.ru");

	url = CHttpUrl("htTps://ersulov.ru");
	REQUIRE(url.GetURL() == "https://ersulov.ru/");
	REQUIRE(url.GetPort() == 443);
	REQUIRE(url.GetDocument() == "/");
	REQUIRE(url.GetDomain() == "ersulov.ru");

	url = CHttpUrl("HTTPS://ersulov.ru:65535/lab1/document/index.php");
	REQUIRE(url.GetURL() == "https://ersulov.ru:65535/lab1/document/index.php");
	REQUIRE(url.GetPort() == 65535);
	REQUIRE(url.GetDocument() == "/lab1/document/index.php");
	REQUIRE(url.GetDomain() == "ersulov.ru");

	url = CHttpUrl("HTTPS://ersulov.ru:65535/lab1/document/index.php?param1=value1&param2=value2");
	REQUIRE(url.GetURL() == "https://ersulov.ru:65535/lab1/document/index.php?param1=value1&param2=value2");
	REQUIRE(url.GetPort() == 65535);
	REQUIRE(url.GetDocument() == "/lab1/document/index.php?param1=value1&param2=value2");
	REQUIRE(url.GetDomain() == "ersulov.ru");
}

TEST_CASE("test CreateURL")
{
	CHttpUrl url = CHttpUrl("ers.ru", "/document");
	REQUIRE(url.GetURL() == "http://ers.ru/document");
	REQUIRE(url.GetPort() == 80);
	REQUIRE(url.GetDocument() == "/document");
	REQUIRE(url.GetDomain() == "ers.ru");

	url = CHttpUrl("ers.ru", "doc");
	REQUIRE(url.GetURL() == "http://ers.ru/doc");
	REQUIRE(url.GetPort() == 80);
	REQUIRE(url.GetDocument() == "/doc");
	REQUIRE(url.GetDomain() == "ers.ru");

	url = CHttpUrl("ers.ru", "doc", Protocol::HTTPS);
	REQUIRE(url.GetURL() == "https://ers.ru/doc");
	REQUIRE(url.GetPort() == 443);
	REQUIRE(url.GetDocument() == "/doc");
	REQUIRE(url.GetDomain() == "ers.ru");

	url = CHttpUrl("ers.ru", "doc", Protocol::HTTPS, 65535);
	REQUIRE(url.GetURL() == "https://ers.ru:65535/doc");
	REQUIRE(url.GetPort() == 65535);
	REQUIRE(url.GetDocument() == "/doc");
	REQUIRE(url.GetDomain() == "ers.ru");
}

TEST_CASE("test CreateURLFailed")
{
	REQUIRE_THROWS_AS(CHttpUrl("", "", Protocol::HTTPS), InvalidDomainException);
	REQUIRE_THROWS_AS(CHttpUrl("example..com", "", Protocol::HTTPS), InvalidDomainException);
	REQUIRE_THROWS_AS(CHttpUrl("quiz.ru ", "", Protocol::HTTPS), InvalidDomainException);
	REQUIRE_THROWS_AS(CHttpUrl("xqz.com", "", Protocol::HTTPS, 0), PortOutOfRangeException);
	REQUIRE_THROWS_AS(CHttpUrl("xqz.com", "", Protocol::HTTPS, 65536), PortOutOfRangeException);
}

TEST_CASE("test ParseURLFailed")
{
	REQUIRE_THROWS_AS(CHttpUrl(""), CUrlParsingError);
	REQUIRE_THROWS_AS(CHttpUrl("ftp://ers"), CUrlParsingError);
	REQUIRE_THROWS_AS(CHttpUrl("http:///"), CUrlParsingError);
	REQUIRE_THROWS_AS(CHttpUrl("http://example..com:20/index.php"), CUrlParsingError);
	REQUIRE_THROWS_AS(CHttpUrl("http://example com:20/index.php"), CUrlParsingError);
	REQUIRE_THROWS_AS(CHttpUrl("http://ersulov.ru:0/index.php"), PortOutOfRangeException);
	REQUIRE_THROWS_AS(CHttpUrl("http://ersulov.ru:65536/index.php"), PortOutOfRangeException);
	REQUIRE_THROWS_AS(CHttpUrl("http://ersulov.ru:-65536/index.php"), PortOutOfRangeException);
	REQUIRE_THROWS_AS(CHttpUrl("http://ersulov.ru:hg/index.php"), InvalidPortException);
}
