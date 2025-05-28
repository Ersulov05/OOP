#pragma once
#include "./IPerson.h"
#include <string>

class IStudent : public IPerson
{
public:
	virtual ~IStudent() = default;

	virtual std::string GetUniversityName() const = 0;
	virtual std::string GetStudentTicketNumber() const = 0;

	virtual void SetUniversityName(const std::string& universityName) = 0;
	virtual void SetStudentTicketNumber(const std::string& studentTicketNumber) = 0;
};