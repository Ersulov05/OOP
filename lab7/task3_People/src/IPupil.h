#pragma once
#include "./IPerson.h"
#include <string>

class IPupil : public IPerson
{
public:
	virtual ~IPupil() = default;

	virtual std::string GetSchoolName() const = 0;
	virtual std::string GetClassName() const = 0;

	virtual void SetSchoolName(const std::string& schoolName) = 0;
	virtual void SetClassName(const std::string& className) = 0;
};