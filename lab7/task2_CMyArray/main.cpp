#include "./src/CMyArray.h"
#include <iostream>

int main()
{
	CMyArray<int> intArray;
	intArray.Add(8);
	intArray.Add(9);
	intArray.Add(10);
	intArray.Add(11);
	intArray.Resize(2);
	// std::cout << intArray.Size() << std::endl;
	for (auto value : intArray)
	{
		std::cout << value << std::endl;
	}
	std::cout << "resize\n";
	intArray.Resize(10);
	// std::cout << intArray.Size() << std::endl;
	for (auto value : intArray)
	{
		std::cout << value << std::endl;
	}
	// std::cout << intArray[10] << std::endl;
	return 0;
}