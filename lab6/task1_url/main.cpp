#include "./src/CHttpUrl.h"
#include <iostream>

void UrlHandler(const std::string& stringUrl, std::ostream& output)
{
	try
	{
		CHttpUrl url(stringUrl);
		output << url.GetURLInfo() << std::endl;
	}
	catch (const std::exception& e)
	{
		output << e.what() << std::endl;
	}
}

int main()
{
	std::string line;
	while (getline(std::cin, line))
	{
		UrlHandler(line, std::cout);
	}
	return 0;
}