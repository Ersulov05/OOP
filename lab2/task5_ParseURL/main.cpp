#include "ParseURL.h"
#include <iostream>

struct URL
{
	Protocol protocol;
	int port = 0;
	std::string host;
	std::string document;
};

void PrintParsedURL(std::ostream& output, const URL& url)
{
	output << "HOST: " << url.host << std::endl;
	output << "PORT: " << url.port << std::endl;
	output << "DOC: " << url.document << std::endl;
}

int main(int argc, char* argv[])
{
	try
	{
		std::string urlString;
		getline(std::cin, urlString);
		URL url;
		ParseURL(urlString, url.protocol, url.port, url.host, url.document);
		std::cout << urlString << std::endl;
		PrintParsedURL(std::cout, url);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}