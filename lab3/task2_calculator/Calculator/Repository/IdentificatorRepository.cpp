#include "./IdentificatorRepository.h"
#include "../Entity/FunctionIdentificator.h"
#include "../Entity/VariableIdentificator.h"

IdentificatorRepository::~IdentificatorRepository()
{
	for (auto& [key, ptr] : m_identificators)
	{
		delete ptr;
	}
	m_identificators.clear();
}

void IdentificatorRepository::StoreIdentificator(IIdentificator* identificator)
{
	m_identificators[identificator->GetName()] = identificator;
}

IIdentificator* IdentificatorRepository::GetIdentificatorByName(const std::string& name)
{
	auto it = m_identificators.find(name);
	if (it == m_identificators.end())
	{
		return nullptr;
	}
	return it->second;
}

std::vector<IIdentificator*> IdentificatorRepository::getVariables()
{
	std::vector<IIdentificator*> variables;
	for (const auto& [name, identificator] : m_identificators)
	{
		if (dynamic_cast<VariableIdentificator*>(identificator))
		{
			variables.push_back(identificator);
		}
	}
	return variables;
}

std::vector<IIdentificator*> IdentificatorRepository::getFunctions()
{
	std::vector<IIdentificator*> functions;
	for (const auto& [name, identificator] : m_identificators)
	{
		if (dynamic_cast<FunctionIdentificator*>(identificator))
		{
			functions.push_back(identificator);
		}
	}
	return functions;
}
