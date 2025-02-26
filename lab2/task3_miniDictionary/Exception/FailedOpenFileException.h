#ifndef FAILED_OPEN_FILE_EXCEPTION_H
#define FAILED_OPEN_FILE_EXCEPTION_H
#include <iostream>

class FailedOpenFileException : public std::runtime_error
{
public:
	FailedOpenFileException()
		: std::runtime_error("Failed open file"){};
};
#endif