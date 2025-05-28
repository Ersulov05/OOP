#pragma once
#include "./IStudent.h"
#include <string>

class IAdvancedStudent : public IStudent
{
public:
	virtual ~IAdvancedStudent() = default;

	virtual std::string GetDissertationTheme() const = 0;

	virtual void SetDissertationTheme(const std::string& dissertationTheme) = 0;
};