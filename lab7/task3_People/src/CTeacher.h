#pragma once
#include "./CPersonImpl.h"
#include "./ITeacher.h"
#include <string>

class CTeacher : public CPersonImpl<ITeacher>
{
public:
	CTeacher(
		const std::string& firstName,
		const std::string& secondName,
		const std::string& thirdName,
		const std::string& addres,
		const std::string& subjectName);

	std::string GetSubjectName() const override;

	void SetSubjectName(const std::string& subjectName) override;

private:
	std::string m_subjectName;
};

CTeacher::CTeacher(
	const std::string& firstName,
	const std::string& secondName,
	const std::string& thirdName,
	const std::string& addres,
	const std::string& subjectName)
	: CPersonImpl<ITeacher>(
		  firstName,
		  secondName,
		  thirdName,
		  addres)
	, m_subjectName(subjectName)
{
}

std::string CTeacher::GetSubjectName() const
{
	return m_subjectName;
}

void CTeacher::SetSubjectName(const std::string& subjectName)
{
	m_subjectName = subjectName;
}