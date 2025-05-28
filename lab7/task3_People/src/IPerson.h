#pragma once
#include <string>

class IPerson
{
public:
	virtual ~IPerson() = default;

	virtual std::string GetFirstName() const = 0;
	virtual std::string GetSecondName() const = 0;
	virtual std::string GetThirdName() const = 0;
	virtual std::string GetAddres() const = 0;

	virtual void SetFirstName(const std::string& firstName) = 0;
	virtual void SetSecondName(const std::string& secondName) = 0;
	virtual void SetThirdName(const std::string& thirdName) = 0;
	virtual void SetAddress(const std::string& address) = 0;
};