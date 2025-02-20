// Ерсулов Андрей ПС-21, лабораторная №1
// Среда Visual Studio Code
// Компилятор g++ c++20

// std::string создаётся инициализированной
// поправить название переменных File
// аргументы консоли через ParseArgs
// форматирование

#include <fstream>
#include <iostream>
#include <optional>

std::string ReplaceLine(const std::string& string,
	const std::string& searchString,
	const std::string& replaceString)
{
	size_t pos = 0;
	size_t foundPos = 0;
	std::string result;
	while ((foundPos = string.find(searchString, pos)) != std::string::npos)
	{
		result.append(string, pos, foundPos - pos);
		result.append(replaceString);

		pos = foundPos + searchString.length();
	}
	result.append(string, pos, string.length() - pos);

	return result;
}

void CopyStreamWithReplacement(
	std::istream& input, std::ostream& output,
	const std::string& searchString,
	const std::string& replaceString)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (searchString == "")
		{
			output << line << std::endl;
		}
		else
		{
			output << ReplaceLine(line, searchString, replaceString) << std::endl;
		}
	}
}

void PrintHelp()
{
	std::cout << "running a program with arguments\n";
	std::cout << "\treplace.exe <input file> <output file> <search string> "
				 "<replace string>\n\n";
	std::cout << "running the program without arguments\n";
	std::cout << "\tthe first line is - the desired line\n";
	std::cout << "\tsecond line - substitute line\n";
	std::cout << "\tthen the replacement text\n";
}

struct Arg
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
	bool isHelp = false;
};

std::optional<Arg> ParseArgs(int argc, char* argv[])
{
	if (argc == 1)
	{
		return std::nullopt;
	}

	Arg arg;
	if (argc == 2 && std::string(argv[1]) == "-h")
	{
		arg.isHelp = true;
		return arg;
	}
	if (argc != 5)
	{
		std::cout << "ERROR\n";
		exit(1);
	}

	arg.inputFileName = argv[1];
	arg.outputFileName = argv[2];
	arg.searchString = argv[3];
	arg.replaceString = argv[4];
	return arg;
}

int main(int argc, char* argv[])
{
	std::optional<Arg> arg = ParseArgs(argc, argv);
	if (arg)
	{
		if (arg->isHelp)
		{
			PrintHelp();
			return 0;
		}
		std::ifstream inputFile(arg->inputFileName);
		if (!inputFile.is_open())
		{
			std::cout << "ERROR\n";
			return 1;
		}
		std::ofstream outputFile(arg->outputFileName);
		if (!outputFile.is_open())
		{
			std::cout << "ERROR\n";
			return 1;
		}

		CopyStreamWithReplacement(inputFile, outputFile, arg->searchString, arg->replaceString);

		inputFile.close();
		outputFile.close();
	}
	else
	{
		std::string searchString = "";
		std::string replaceString = "";
		std::getline(std::cin, searchString);
		std::getline(std::cin, replaceString);
		if (std::cin.eof())
		{
			std::cout << "ERROR\n";
			return 0;
		}

		CopyStreamWithReplacement(std::cin, std::cout, searchString, replaceString);
	}

	return 0;
}