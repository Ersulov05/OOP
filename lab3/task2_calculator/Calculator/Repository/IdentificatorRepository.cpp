#include "./IdentificatorRepository.h"
#include "../Exception/IdentificatorNameExistsException.h"
#include "../Exception/IdentificatorTypeNotIsVariableException.h"
#include <iostream>

IdentificatorRepository::IdentificatorRepository() {}

void IdentificatorRepository::AddIdentificator(const Identificator& identificator)
{
	IdentificatorRepository::AssertIdentificatorNameNotExists(identificator.name);
	this->m_identificators[identificator.name] = identificator;
}

void IdentificatorRepository::StoreVariableIdentificator(const Identificator& identificator)
{
	std::optional<Identificator> existIdentificator = GetIdentificatorByName(identificator.name);
	if (existIdentificator)
	{
		IdentificatorRepository::AssertIdentificatorTypeIsVariable(existIdentificator->type);
	}
	IdentificatorRepository::AssertIdentificatorTypeIsVariable(identificator.type);
	this->m_identificators[identificator.name] = identificator;
}

std::optional<Identificator> IdentificatorRepository::GetIdentificatorByName(const std::string& identificatorName) const
{
	auto it = m_identificators.find(identificatorName);
	if (it != m_identificators.end())
	{
		return it->second;
	}
	return std::nullopt;
}

std::unordered_map<std::string, Identificator> IdentificatorRepository::GetVariableIdentificators() const
{
	std::unordered_map<std::string, Identificator> variableIdentificators;
	for (const auto& pair : this->m_identificators)
	{
		if (pair.second.type == IdentificatorType::VARIABLE)
		{
			variableIdentificators[pair.first] = pair.second;
		}
	}

	return variableIdentificators;
}

std::unordered_map<std::string, Identificator> IdentificatorRepository::GetFunctionIdentificators() const
{
	std::unordered_map<std::string, Identificator> variableIdentificators;
	for (const auto& pair : m_identificators)
	{
		if (pair.second.type == IdentificatorType::FUNCTION)
		{
			variableIdentificators[pair.first] = pair.second;
		}
	}

	return variableIdentificators;
}

std::unordered_map<std::string, Identificator> IdentificatorRepository::GetAllIdentificators() const
{
	return this->m_identificators;
}

void IdentificatorRepository::AssertIdentificatorNameNotExists(const std::string& identificatorName)
{
	std::optional<Identificator> identificator = GetIdentificatorByName(identificatorName);
	if (identificator)
	{
		throw IdentificatorNameExistsException();
	}
}

void IdentificatorRepository::AssertIdentificatorTypeIsVariable(IdentificatorType identificatorType)
{
	if (identificatorType != IdentificatorType::VARIABLE)
	{
		throw IdentificatorTypeNotIsVariableException();
	}
}
