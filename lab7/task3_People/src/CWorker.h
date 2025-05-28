#pragma once
#include "./CPersonImpl.h"
#include "./IWorker.h"
#include <string>

class CWorker : public CPersonImpl<IWorker>
{
public:
	CWorker(
		const std::string& firstName,
		const std::string& secondName,
		const std::string& thirdName,
		const std::string& addres,
		const std::string& speciality);

	std::string GetSpeciality() const override;

	void SetSpeciality(const std::string& speciality) override;

private:
	std::string m_speciality;
};

CWorker::CWorker(
	const std::string& firstName,
	const std::string& secondName,
	const std::string& thirdName,
	const std::string& addres,
	const std::string& speciality)
	: CPersonImpl<IWorker>(
		  firstName,
		  secondName,
		  thirdName,
		  addres)
	, m_speciality(speciality)
{
}

std::string CWorker::GetSpeciality() const
{
	return m_speciality;
}

void CWorker::SetSpeciality(const std::string& speciality)
{
	m_speciality = speciality;
}