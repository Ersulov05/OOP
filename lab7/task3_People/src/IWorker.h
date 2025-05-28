#pragma once
#include "./IPerson.h"
#include <string>

class IWorker : public IPerson
{
public:
	virtual ~IWorker() = default;

	virtual std::string GetSpeciality() const = 0;

	virtual void SetSpeciality(const std::string& speciality) = 0;
};