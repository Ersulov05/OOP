#include <iostream>

class IncorrectEncryptionDecryptionParameterException : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Incorrect encryption - decryption parameter";
	}
};