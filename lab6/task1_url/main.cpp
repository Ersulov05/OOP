#include "./src/CHttpUrl.h"
#include <iostream>

int main()
{
	CHttpUrl url = CHttpUrl("Http://ersulov.ru/index.php");
	std::cout << url.GetURL() << std::endl;
	std::cout << url.GetDocument() << std::endl;
	return 0;
}