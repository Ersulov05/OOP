#pragma once
#include "./IPerson.h"
#include <string>

class ITeacher : public IPerson
{
public:
	virtual ~ITeacher() = default;

	virtual std::string GetSubjectName() const = 0;

	virtual void SetSubjectName(const std::string& subjectName) = 0;
};