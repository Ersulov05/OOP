// Ерсулов Андрей ПС-21, лабораторная №1
// Среда Visual Studio Code
// Компилятор g++ c++20

#include "Exception/DeterminantEqualsZeroException.h"
#include "Exception/InvalidArgumentsException.h"
#include "Exception/InvalidMatrixFormatException.h"
#include "Exception/InvalidMatrixValueException.h"
#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>

double removeNegativeZero(double value)
{
	if (value == 0 && std::signbit(value))
	{
		return 0;
	}
	return value;
}

double roundToDecimal(double number, int decimals)
{
	double factor = std::pow(10, decimals);
	return removeNegativeZero(std::round(number * factor) / factor);
}

template <std::size_t Rows, std::size_t Columns>
using Matrix = std::array<std::array<double, Columns>, Rows>;

template <std::size_t Rows, std::size_t Columns>
Matrix<Rows - 1, Columns - 1> GetMinor(const Matrix<Rows, Columns>& matrix, std::size_t row, std::size_t column)
{
	Matrix<Rows - 1, Columns - 1> minor;
	size_t minorRow = 0;
	for (size_t i = 0; i < Rows; ++i)
	{
		if (i != row)
		{
			size_t minorColumn = 0;
			for (size_t j = 0; j < Columns; ++j)
			{
				if (j != column)
				{
					minor[minorRow][minorColumn] = matrix[i][j];
					minorColumn++;
				}
			}
			minorRow++;
		}
	}
	return minor;
}

double GetDeterminantMatrix(const Matrix<1, 1>& matrix)
{
	return matrix[0][0];
}

double GetDeterminantMatrix(const Matrix<2, 2>& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

template <std::size_t N>
double GetDeterminantMatrix(const Matrix<N, N>& matrix)
{
	double determinant = 0;
	for (std::size_t i = 0; i < N; ++i)
	{
		auto minor = GetMinor(matrix, 0, i);
		int sign = i % 2 == 0 ? 1 : -1;
		determinant += sign * matrix[0][i] * GetDeterminantMatrix(minor);
	}

	return determinant;
}

template <std::size_t Rows, std::size_t Columns>
Matrix<Columns, Rows> TransposeMatrix(const Matrix<Rows, Columns>& matrix)
{
	Matrix<Columns, Rows> transposedMatrix;
	for (unsigned i = 0; i < Rows; ++i)
	{
		for (unsigned j = 0; j < Columns; ++j)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}
	return transposedMatrix;
}

template <std::size_t Rows, std::size_t Columns>
void PrintMatrix(std::ostream& output, const Matrix<Rows, Columns>& matrix, std::string separator = " ")
{
	for (std::size_t i = 0; i < Rows; ++i)
	{
		for (std::size_t j = 0; j < Columns; ++j)
		{
			output << std::fixed << std::setprecision(3) << roundToDecimal(matrix[i][j], 3);
			if (j < Columns - 1)
			{
				output << separator;
			}
		}
		output << std::endl;
	}
}

template <std::size_t N>
Matrix<N, N> MultiplyMatrixOnScalar(const Matrix<N, N>& matrix, double scalar)
{
	Matrix<N, N> resultMatrix;
	for (std::size_t i = 0; i < N; ++i)
	{
		for (std::size_t j = 0; j < N; ++j)
		{
			resultMatrix[i][j] = matrix[i][j] * scalar;
		}
	}
	return resultMatrix;
}

void assertDeterminantNotEqualsZero(double determinant)
{
	if (determinant == 0)
	{
		throw DeterminantEqualsZeroException();
	}
}

template <std::size_t N>
Matrix<N, N> GetMatrixAlgebraicAdditions(const Matrix<N, N>& matrix)
{
	Matrix<N, N> resultMatrix;

	for (std::size_t i = 0; i < N; ++i)
	{
		for (std::size_t j = 0; j < N; ++j)
		{
			int sign = (i + j) % 2 == 0 ? 1 : -1;
			resultMatrix[i][j] = GetDeterminantMatrix(GetMinor(matrix, i, j)) * sign;
		}
	}
	return resultMatrix;
}

template <std::size_t N>
Matrix<N, N> GetReverseMatrix(const Matrix<N, N>& matrix)
{
	auto determinant = GetDeterminantMatrix(matrix);
	assertDeterminantNotEqualsZero(determinant);
	Matrix<N, N> transposeMatrix = GetMatrixAlgebraicAdditions(TransposeMatrix(matrix));
	return MultiplyMatrixOnScalar(transposeMatrix, 1 / determinant);
}

void assertDimensionNotExceeded(std::size_t actual, std::size_t maxAllowed)
{
	if (actual > maxAllowed)
	{
		throw InvalidMatrixFormatException();
	}
}

void assertDimensionMatch(std::size_t actual, std::size_t expected)
{
	if (actual != expected)
	{
		throw InvalidMatrixFormatException();
	}
}

template <std::size_t Rows, std::size_t Columns>
void ReadRowMatrix(std::string& line, Matrix<Rows, Columns>& matrix, std::size_t row)
{
	std::istringstream iss(line);
	std::string item;
	std::size_t col = 0;

	while (std::getline(iss, item, '\t'))
	{
		assertDimensionNotExceeded(col + 1, Columns);
		double value = 0;
		try
		{
			value = std::stod(item);
		}
		catch (const std::exception& e)
		{
			throw InvalidMatrixValueException();
		}

		matrix[row][col] = value;
		col++;
	}
	assertDimensionMatch(col, Columns);
}

template <std::size_t Rows, std::size_t Columns>
void ReadMatrix(std::istream& input, Matrix<Rows, Columns>& matrix)
{
	std::string line;
	std::size_t row = 0;

	while (std::getline(input, line))
	{
		assertDimensionNotExceeded(row + 1, Rows);
		ReadRowMatrix(line, matrix, row);
		row++;
	}
	assertDimensionMatch(row, Rows);
}

void PrintHelp()
{
	std::cout << "help\n";
}

struct Arg
{
	std::string inputFileName;
	bool isHelp;
};

std::optional<Arg> ParseArgs(int argc, char* argv[])
{
	if (argc == 1)
		return std::nullopt;

	Arg arg = { "", false };
	if (argc == 2)
	{
		std::string firstArg = argv[1];
		arg.isHelp = firstArg == "-h";
		if (!arg.isHelp)
		{
			arg.inputFileName = firstArg;
		}
		return arg;
	}
	throw InvalidArgumentsException();
}

int main(int argc, char* argv[])
{
	const std::size_t MATRIX_SIZE = 3;
	Matrix<MATRIX_SIZE, MATRIX_SIZE> matrix;

	try
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
				std::cout << "Failed to open input file" << std::endl;
				return 1;
			}
			ReadMatrix(inputFile, matrix);
		}
		else
		{
			ReadMatrix(std::cin, matrix);
		}
		auto reverseMatrix = GetReverseMatrix(matrix);
		PrintMatrix(std::cout, reverseMatrix, "\t");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}