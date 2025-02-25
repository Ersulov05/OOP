#include <iostream>

class IncorrectEncryptionDecryptionParameterException : public std::runtime_error
{
public:
	IncorrectEncryptionDecryptionParameterException()
		: std::runtime_error("Incorrect encryption - decryption parameter"){};
};