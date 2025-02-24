// Ерсулов Андрей ПС-21, лабораторная №1
// Среда Visual Studio Code
// Компилятор g++ c++20

#include "Exception/FailedOpenFileException.h"
#include "Exception/InputOutputFileNameMatchException.h"
#include "Exception/InvalidArgumentCountException.h"
#include "Exception/InvalidSymbolException.h"
#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

const int EXPECTED_ARG_COUNT = 3;
const int EXPECTED_HELP_ARG_COUNT = 2;
const char POINT_SYMBOL = 'O';
const char WALL_SYMBOL = '#';
const char FILL_SYMBOL = '.';
const char EMPTY_SYMBOL = ' ';
const char EMPTY_LINE_SYMBOL = '/';
const char NO_USED_CELL = '*';
const std::size_t ROW_COUNT = 100;
const std::size_t COLUMN_COUNT = 100;

struct Point
{
	std::size_t rowIndex;
	std::size_t columnIndex;
};

template <typename std::size_t Rows, std::size_t Columns>
using Map = std::array<std::array<char, Columns>, Rows>;

struct Arg
{
	bool isHelp = false;
	std::string inputFileName;
	std::string outputFileName;
};

void assertInputOutputFileNameMismatch(const std::string& inputFileName, const std::string& outputFileName)
{
	if (inputFileName == outputFileName)
	{
		throw InputOutputFileNameMatchException();
	}
}

std::optional<Arg> ParseArgs(int argc, char* argv[])
{
	if (argc > 3)
	{
		throw InvalidArgumentCountException();
	}
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
	arg.inputFileName = argv[1];
	arg.outputFileName = argv[2];
	assertInputOutputFileNameMismatch(arg.inputFileName, arg.outputFileName);
	return arg;
}

void asserCorrectSymbol(char symbol)
{
	if (symbol != EMPTY_SYMBOL && symbol != POINT_SYMBOL && symbol != WALL_SYMBOL)
	{
		throw InvalidSymbolException();
	}
}

template <typename std::size_t Rows, std::size_t Columns>
void loadMap(std::istream& input, Map<Rows, Columns>& map, std::vector<Point>& pointList)
{
	std::string line;
	std::size_t row = 0;
	while (getline(input, line))
	{
		if (line.empty())
		{
			map[row][0] = EMPTY_LINE_SYMBOL;
			row++;
			continue;
		}
		if (row + 1 > Rows)
		{
			break;
		}

		std::size_t lineSize = line.size() > Columns ? Columns : line.size();

		for (size_t col = 0; col < lineSize; ++col)
		{
			char ch = line[col];
			asserCorrectSymbol(ch);
			map[row][col] = ch;
			if (ch == POINT_SYMBOL)
			{
				pointList.push_back({ row, col });
			}
		}
		row++;
	}
}

template <typename std::size_t Rows, std::size_t Columns>
Map<Rows, Columns> getEmptyMap()
{
	Map<Rows, Columns> newMap;
	for (std::size_t i = 0; i < Rows; ++i)
	{
		for (std::size_t j = 0; j < Columns; ++j)
		{
			newMap[i][j] = NO_USED_CELL;
		}
	}
	return newMap;
}

template <typename std::size_t Rows, std::size_t Columns>
void fillPointMap(Map<Rows, Columns>& map, const Point& point)
{
	if (point.rowIndex < 0
		|| point.columnIndex < 0
		|| point.columnIndex >= Rows
		|| point.rowIndex >= Columns
		|| map[point.rowIndex][point.columnIndex] == FILL_SYMBOL
		|| map[point.rowIndex][point.columnIndex] == WALL_SYMBOL
		|| map[point.rowIndex][point.columnIndex] == POINT_SYMBOL)
	{
		return;
	}
	map[point.rowIndex][point.columnIndex] = FILL_SYMBOL;
	fillPointMap(map, { point.rowIndex - 1, point.columnIndex });
	fillPointMap(map, { point.rowIndex + 1, point.columnIndex });
	fillPointMap(map, { point.rowIndex, point.columnIndex - 1 });
	fillPointMap(map, { point.rowIndex, point.columnIndex + 1 });
}

template <typename std::size_t Rows, std::size_t Columns>
void fillMap(Map<Rows, Columns>& map, std::vector<Point>& pointList)
{
	for (const auto point : pointList)
	{
		fillPointMap(map, { point.rowIndex - 1, point.columnIndex });
		fillPointMap(map, { point.rowIndex + 1, point.columnIndex });
		fillPointMap(map, { point.rowIndex, point.columnIndex - 1 });
		fillPointMap(map, { point.rowIndex, point.columnIndex + 1 });
	}
}

template <typename std::size_t Rows, std::size_t Columns>
void printMap(std::ostream& output, Map<Rows, Columns>& map)
{
	for (std::size_t i = 0; i < Rows; ++i)
	{
		if (map[i][0] == EMPTY_LINE_SYMBOL)
		{
			output << std::endl;
			continue;
		}
		if (map[i][0] == NO_USED_CELL)
		{
			break;
		}
		for (std::size_t j = 0; j < Columns; ++j)
		{
			char symbol = map[i][j];
			if (symbol == NO_USED_CELL)
			{
				break;
			}
			output << map[i][j];
		}
		output << std::endl;
	}
}

void PrintHelp()
{
	std::cout << "help\n";
}

int main(int argc, char* argv[])
{
	try
	{
		std::optional<Arg> arg = ParseArgs(argc, argv);
		std::vector<Point> pointList;
		auto map = getEmptyMap<ROW_COUNT, COLUMN_COUNT>();
		if (arg)
		{
			if (arg->isHelp)
			{
				PrintHelp();
				return 0;
			}
			std::ifstream inputFile(arg->inputFileName);
			std::ofstream outputFile(arg->outputFileName);

			if (!inputFile.is_open())
			{
				throw FailedOpenFileException();
			}
			if (!outputFile.is_open())
			{
				throw FailedOpenFileException();
			}

			loadMap(inputFile, map, pointList);
			fillMap(map, pointList);
			printMap(outputFile, map);

			inputFile.close();
			outputFile.close();
		}
		else
		{
			loadMap(std::cin, map, pointList);
			fillMap(map, pointList);
			printMap(std::cout, map);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR" << std::endl; // e.what()
		if (argc > 1)
		{
			return 1;
		}
		return 0;
	}

	return 0;
}