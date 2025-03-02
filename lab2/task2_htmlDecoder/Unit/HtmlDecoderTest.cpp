#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../HtmlDecoder.h"

TEST_CASE("test GetHTMLDecode")
{
	struct InputOutputGetHTMLDecode
	{
		std::string inputString;
		std::string outputString;
	};

	std::vector<InputOutputGetHTMLDecode> testsData = {
		{ "hello", "hello" },
		{ "&quot;", "\"" },
		{ "&amp;", "&" },
		{ "&apos;", "\'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&gt", "&gt" },
		{ "&apos;;", "&apos;;" }
	};

	for (const InputOutputGetHTMLDecode& testData : testsData)
	{
		REQUIRE(GetHTMLDecode(testData.inputString) == testData.outputString);
	}
}

TEST_CASE("test DecodeHTMLString")
{
	struct InputOutputDecodeHTMLString
	{
		std::string inputString;
		std::string outputString;
	};

	std::vector<InputOutputDecodeHTMLString> testsData = {
		{ "hello", "hello" },
		{ "@@@&quot;@@@", "@@@\"@@@" },
		{ "&&amp;", "&&" },
		{ ";&&apos;", ";&\'" },
		{ "&&lt;&", "&<&" },
		{ ";&gt;;", ";>;" },
		{ "& ; && ;&gt", "& ; && ;&gt" },
		{ "&apos;;", "\';" },
		{ "&amp;&quot;&gt;&lt;&apos;", "&\"><\'" },
	};

	for (InputOutputDecodeHTMLString testData : testsData)
	{
		REQUIRE(DecodeHTMLString(testData.inputString) == testData.outputString);
	}
}