// Ерсулов Андрей ПС-21, лабораторная №1
// Среда Visual Studio Code
// Компилятор g++ c++20

#include "Exception/FailedOpenFileException.h"
#include "Exception/IncorrectEncryptionDecryptionParameterException.h"
#include "Exception/InputOutputFileNameMatchException.h"
#include "Exception/InvalidArgumentCountException.h"
#include "Exception/InvalidKeyValueException.h"
#include "Exception/KeyValueOutOfRangeException.h"
#include <fstream>
#include <iostream>
#include <limits>

const std::string CRYPT_OPERATION = "crypt";
const std::string DECRYPT_OPERATION = "decrypt";
const int EXPECTED_ARG_COUNT = 5;

struct Arg
{
	bool isCrypt = false;
	std::string outputFileName;
	std::string inputFileName;
	u_int8_t key = 0;
};

void AssertInputOutputFileNameMismatch(const std::string& inputFileName, const std::string& outputFileName)
{
	if (inputFileName == outputFileName)
	{
		throw InputOutputFileNameMatchException();
	}
}

void AssertCorectnessEncryptionDecryptionParameter(const std::string& operation)
{
	if (operation != CRYPT_OPERATION && operation != DECRYPT_OPERATION)
	{
		throw IncorrectEncryptionDecryptionParameterException();
	}
}

void AssertExpectedArgumentCount(int argc)
{
	if (argc != EXPECTED_ARG_COUNT)
	{
		throw InvalidArgumentCountException();
	}
}

u_int8_t getKeyFromString(const std::string& str)
{
	if (str.empty())
	{
		throw InvalidKeyValueException();
	}

	int result = 0;

	for (char ch : str)
	{
		if (!std::isdigit(ch))
		{
			throw InvalidKeyValueException();
		}

		result = result * 10 + (ch - '0');

		if (result > __UINT8_MAX__)
		{
			throw KeyValueOutOfRangeException();
		}
	}

	return static_cast<u_int8_t>(result);
}

Arg ParseArgs(int argc, char* argv[])
{
	AssertExpectedArgumentCount(argc);

	Arg arg;
	std::string firstArg = argv[1];
	AssertCorectnessEncryptionDecryptionParameter(firstArg);

	arg.isCrypt = firstArg == "crypt" ? true : false;
	arg.inputFileName = argv[2];
	arg.outputFileName = argv[3];

	AssertInputOutputFileNameMismatch(arg.inputFileName, arg.outputFileName);

	arg.key = getKeyFromString(argv[4]);
	return arg;
}

u_int8_t CryptByte(const u_int8_t byte, u_int8_t key)
{
	u_int8_t byteXOR = byte ^ key;
	u_int8_t result = 0;

	result |= (byteXOR << 2) & 0b00011100;
	result |= (byteXOR >> 5) & 0b00000011;
	result |= (byteXOR >> 2) & 0b00100000;
	result |= (byteXOR << 3) & 0b11000000;

	return result;
}

u_int8_t DecryptByte(const u_int8_t byte, u_int8_t key)
{
	u_int8_t result = 0;

	result |= (byte >> 2) & 0b00000111;
	result |= (byte << 5) & 0b01100000;
	result |= (byte << 2) & 0b10000000;
	result |= (byte >> 3) & 0b00011000;

	return result ^ key;
}

void CryptBytes(std::istream& input, std::ostream& output, u_int8_t key)
{
	char byte = 0;
	while (input.get(byte))
	{
		u_int8_t encryptedByte = CryptByte(byte, key);
		output.put(encryptedByte);
	}
}

void DecryptBytes(std::istream& input, std::ostream& output, u_int8_t key)
{
	char byte = 0;
	while (input.get(byte))
	{
		u_int8_t encryptedByte = DecryptByte(byte, key);
		output.put(encryptedByte);
	}
}

int main(int argc, char* argv[])
{
	try
	{
		Arg arg = ParseArgs(argc, argv);
		std::ifstream inputFile(arg.inputFileName, std::ios::binary);
		std::ofstream outputFile(arg.outputFileName, std::ios::binary);

		if (!inputFile.is_open())
		{
			throw FailedOpenFileException();
		}
		if (!outputFile.is_open())
		{
			throw FailedOpenFileException();
		}

		if (arg.isCrypt)
		{
			CryptBytes(inputFile, outputFile, arg.key);
		}
		else
		{
			DecryptBytes(inputFile, outputFile, arg.key);
		}

		inputFile.close();
		outputFile.close();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}