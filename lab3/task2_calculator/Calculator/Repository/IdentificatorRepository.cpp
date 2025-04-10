#include "./IdentificatorRepository.h"
#include "../Entity/Function.h"
#include "../Entity/Variable.h"

IdentificatorRepository::~IdentificatorRepository()
{
	for (auto& [key, ptr] : m_identificators)
	{
		delete ptr;
	}
	m_identificators.clear();
}

void IdentificatorRepository::StoreIdentificator(Identificator* identificator)
{
	m_identificators[identificator->GetName()] = identificator;
}

Identificator* IdentificatorRepository::GetIdentificatorByName(const std::string& name)
{
	auto it = m_identificators.find(name);
	if (it == m_identificators.end())
	{
		return nullptr;
	}
	return it->second;
}

std::vector<Identificator*> IdentificatorRepository::GetVariables()
{
	std::vector<Identificator*> variables;
	for (const auto& [name, identificator] : m_identificators)
	{
		if (dynamic_cast<Variable*>(identificator))
		{
			variables.push_back(identificator);
		}
	}
	return variables;
}

std::vector<Identificator*> IdentificatorRepository::GetFunctions()
{
	std::vector<Identificator*> functions;
	for (const auto& [name, identificator] : m_identificators)
	{
		if (dynamic_cast<Function*>(identificator))
		{
			functions.push_back(identificator);
		}
	}
	return functions;
}
