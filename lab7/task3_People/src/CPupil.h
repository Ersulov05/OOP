#pragma once
#include "./CPersonImpl.h"
#include "./IPupil.h"
#include <string>

class CPupil : public CPersonImpl<IPupil>
{
public:
	CPupil(
		const std::string& firstName,
		const std::string& secondName,
		const std::string& thirdName,
		const std::string& addres,
		const std::string& schoolName,
		const std::string& className);

	std::string GetSchoolName() const override;
	std::string GetClassName() const override;

	void SetSchoolName(const std::string& schoolName) override;
	void SetClassName(const std::string& className) override;

private:
	std::string m_schoolName;
	std::string m_className;
};

CPupil::CPupil(
	const std::string& firstName,
	const std::string& secondName,
	const std::string& thirdName,
	const std::string& addres,
	const std::string& schoolName,
	const std::string& className)
	: CPersonImpl<IPupil>(
		  firstName,
		  secondName,
		  thirdName,
		  addres)
	, m_schoolName(schoolName)
	, m_className(className)
{
}

std::string CPupil::GetSchoolName() const
{
	return m_schoolName;
}

std::string CPupil::GetClassName() const
{
	return m_className;
}

void CPupil::SetSchoolName(const std::string& schoolName)
{
	m_schoolName = schoolName;
}

void CPupil::SetClassName(const std::string& className)
{
	m_className = className;
}