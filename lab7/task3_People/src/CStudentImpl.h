#pragma once
#include "./CPersonImpl.h"
#include <string>

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	CStudentImpl(
		const std::string& firstName,
		const std::string& secondName,
		const std::string& thirdName,
		const std::string& addres,
		const std::string& universityName,
		const std::string& studentTicketNumber);

	std::string GetUniversityName() const override;
	std::string GetStudentTicketNumber() const override;

	void SetUniversityName(const std::string& universityName) override;
	void SetStudentTicketNumber(const std::string& studentTicketNumber) override;

private:
	std::string m_universityName;
	std::string m_studentTicketNumber;
};

template <typename Base>
CStudentImpl<Base>::CStudentImpl(
	const std::string& firstName,
	const std::string& secondName,
	const std::string& thirdName,
	const std::string& addres,
	const std::string& universityName,
	const std::string& studentTicketNumber)
	: CPersonImpl<Base>(
		  firstName,
		  secondName,
		  thirdName,
		  addres)
	, m_universityName(universityName)
	, m_studentTicketNumber(studentTicketNumber)
{
}

template <typename Base>
std::string CStudentImpl<Base>::GetUniversityName() const
{
	return m_universityName;
}

template <typename Base>
std::string CStudentImpl<Base>::GetStudentTicketNumber() const
{
	return m_studentTicketNumber;
}

template <typename Base>
void CStudentImpl<Base>::SetUniversityName(const std::string& universityName)
{
	m_universityName = universityName;
}

template <typename Base>
void CStudentImpl<Base>::SetStudentTicketNumber(const std::string& studentTicketNumber)
{
	m_studentTicketNumber = studentTicketNumber;
}