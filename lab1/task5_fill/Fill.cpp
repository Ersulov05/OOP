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

using Map = std::vector<std::vector<char>>; // заменить на вектор векторов

struct Arg
{
	bool isHelp = false;
	std::string inputFileName;
	std::string outputFileName;
};

void AssertInputOutputFileNameMismatch(const std::string& inputFileName, const std::string& outputFileName)
{
	if (inputFileName == outputFileName)
	{
		throw InputOutputFileNameMatchException();
	}
}

void AssertExpectedArgumentCount(int argc)
{
	if (argc != EXPECTED_ARG_COUNT)
	{
		throw InvalidArgumentCountException();
	}
}

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
	AssertExpectedArgumentCount(argc);
	AssertInputOutputFileNameMismatch(argv[1], argv[2]);

	arg.inputFileName = argv[1];
	arg.outputFileName = argv[2];

	return arg;
}

void AssertCorrectSymbol(char symbol)
{
	if (symbol != EMPTY_SYMBOL && symbol != POINT_SYMBOL && symbol != WALL_SYMBOL)
	{
		throw InvalidSymbolException();
	}
}

Map GetEmptyMap()
{
	return std::vector<std::vector<char>>(ROW_COUNT, std::vector<char>(COLUMN_COUNT, NO_USED_CELL));
}

Map LoadMap(std::istream& input, std::vector<Point>& pointList)
{
	auto map = GetEmptyMap();
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
		if (row + 1 > ROW_COUNT)
		{
			break;
		}

		std::size_t lineSize = line.size() > COLUMN_COUNT ? COLUMN_COUNT : line.size();

		for (size_t col = 0; col < lineSize; ++col)
		{
			char ch = line[col];
			AssertCorrectSymbol(ch);
			map[row][col] = ch;
			if (ch == POINT_SYMBOL)
			{
				pointList.push_back({ row, col });
			}
		}
		row++;
	}
	return map;
}

bool CheckBorders(std::size_t x, std::size_t y)
{
	return x < 0 || y < 0 || x >= ROW_COUNT || y >= COLUMN_COUNT;
}

bool CanFill(std::size_t x, std::size_t y, const Map& map)
{
	return map[y][x] == FILL_SYMBOL
		|| map[y][x] == WALL_SYMBOL
		|| map[y][x] == POINT_SYMBOL;
}

void FillPointMap(Map& map, const Point& point)
{
	if (CheckBorders(point.columnIndex, point.rowIndex) || CanFill(point.columnIndex, point.rowIndex, map))
	{
		return;
	}
	map[point.rowIndex][point.columnIndex] = FILL_SYMBOL;
	FillPointMap(map, { point.rowIndex - 1, point.columnIndex });
	FillPointMap(map, { point.rowIndex + 1, point.columnIndex });
	FillPointMap(map, { point.rowIndex, point.columnIndex - 1 });
	FillPointMap(map, { point.rowIndex, point.columnIndex + 1 });
}

void FillMap(Map& map, const std::vector<Point>& pointList)
{
	for (const auto& point : pointList)
	{
		FillPointMap(map, { point.rowIndex - 1, point.columnIndex });
		FillPointMap(map, { point.rowIndex + 1, point.columnIndex });
		FillPointMap(map, { point.rowIndex, point.columnIndex - 1 });
		FillPointMap(map, { point.rowIndex, point.columnIndex + 1 });
	}
}

void PrintMap(std::ostream& output, Map& map)
{
	for (std::size_t i = 0; i < ROW_COUNT; ++i)
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
		for (std::size_t j = 0; j < COLUMN_COUNT; ++j)
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

void Fill(std::istream& input, std::ostream& output)
{
	std::vector<Point> pointList;
	auto map = LoadMap(input, pointList);
	FillMap(map, pointList);
	PrintMap(output, map);
}

int main(int argc, char* argv[])
{
	try
	{
		std::optional<Arg> arg = ParseArgs(argc, argv);
		if (arg && arg->isHelp)
		{
			PrintHelp();
			return 0;
		}

		std::ifstream inputFile;
		std::ofstream outputFile;
		std::istream& input = arg ? inputFile : std::cin;
		std::ostream& output = arg ? outputFile : std::cout;
		if (arg)
		{
			inputFile.open(arg->inputFileName);
			outputFile.open(arg->outputFileName);

			if (!inputFile.is_open())
			{
				throw FailedOpenFileException();
			}
			if (!outputFile.is_open())
			{
				throw FailedOpenFileException();
			}
		}

		Fill(input, output);
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