#include "./src/CStringList.h"
#include <iostream>

int main()
{
	CStringList stringList;
	stringList.PushBack("hello");
	stringList.PushBack("world");
	stringList.PushBack("!");
	stringList.Insert(stringList.end(), "90");
	for (auto str : stringList)
	{
		std::cout << str << std::endl;
	}
	return 0;
}