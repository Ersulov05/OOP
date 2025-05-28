#pragma once
#include "./CStudentImpl.h"
#include "./IAdvancedStudent.h"
#include <string>

class CAdvancedStudent : public CStudentImpl<IAdvancedStudent>
{
public:
	CAdvancedStudent(
		const std::string& firstName,
		const std::string& secondName,
		const std::string& thirdName,
		const std::string& addres,
		const std::string& universityName,
		const std::string& studentTicketNumber,
		const std::string& dissertationTheme);

	std::string GetDissertationTheme() const override;

	void SetDissertationTheme(const std::string& dissertationTheme) override;

private:
	std::string m_dissertationTheme;
};

CAdvancedStudent::CAdvancedStudent(
	const std::string& firstName,
	const std::string& secondName,
	const std::string& thirdName,
	const std::string& addres,
	const std::string& universityName,
	const std::string& studentTicketNumber,
	const std::string& dissertationTheme)
	: CStudentImpl<IAdvancedStudent>(
		  firstName,
		  secondName,
		  thirdName,
		  addres,
		  universityName,
		  studentTicketNumber)
	, m_dissertationTheme(dissertationTheme)
{
}

std::string CAdvancedStudent::GetDissertationTheme() const
{
	return m_dissertationTheme;
}

void CAdvancedStudent::SetDissertationTheme(const std::string& dissertationTheme)
{
	m_dissertationTheme = dissertationTheme;
}