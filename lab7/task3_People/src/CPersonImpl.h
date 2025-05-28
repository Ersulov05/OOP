#pragma once
#include <string>

template <typename Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl(
		const std::string& firstName,
		const std::string& secondName,
		const std::string& thirdName,
		const std::string& addres);

	virtual std::string GetFirstName() const override;
	virtual std::string GetSecondName() const override;
	virtual std::string GetThirdName() const override;
	virtual std::string GetAddres() const override;

	virtual void SetFirstName(const std::string& firstName) override;
	virtual void SetSecondName(const std::string& secondName) override;
	virtual void SetThirdName(const std::string& thirdName) override;
	virtual void SetAddress(const std::string& address) override;

private:
	std::string m_firstName;
	std::string m_secondName;
	std::string m_thirdName;
	std::string m_addres;
};

template <typename Base>
CPersonImpl<Base>::CPersonImpl(
	const std::string& firstName,
	const std::string& secondName,
	const std::string& thirdName,
	const std::string& addres)
	: m_firstName(firstName)
	, m_secondName(secondName)
	, m_thirdName(thirdName)
	, m_addres(addres)
{
}

template <typename Base>
std::string CPersonImpl<Base>::GetFirstName() const
{
	return m_firstName;
}

template <typename Base>
std::string CPersonImpl<Base>::GetSecondName() const
{
	return m_secondName;
}

template <typename Base>
std::string CPersonImpl<Base>::GetThirdName() const
{
	return m_thirdName;
}

template <typename Base>
std::string CPersonImpl<Base>::GetAddres() const
{
	return m_addres;
}

template <typename Base>
void CPersonImpl<Base>::SetFirstName(const std::string& firstName)
{
	m_firstName = firstName;
}

template <typename Base>
void CPersonImpl<Base>::SetSecondName(const std::string& secondName)
{
	m_secondName = secondName;
}

template <typename Base>
void CPersonImpl<Base>::SetThirdName(const std::string& thirdName)
{
	m_thirdName = thirdName;
}

template <typename Base>
void CPersonImpl<Base>::SetAddress(const std::string& address)
{
	m_addres = address;
}
