#include "./IdentificatorRepository.h"
#include "../Entity/FunctionIdentificator.h"
#include "../Entity/VariableIdentificator.h"

void IdentificatorRepository::StoreIdentificator(std::shared_ptr<IIdentificator> identificator)
{
	m_identificators[identificator->GetName()] = identificator;
}

std::shared_ptr<IIdentificator> IdentificatorRepository::GetIdentificatorByName(const std::string& name)
{
	auto it = m_identificators.find(name);
	if (it == m_identificators.end())
	{
		return nullptr;
	}
	return it->second;
}

std::vector<std::shared_ptr<IIdentificator>> IdentificatorRepository::getVariables()
{
	std::vector<std::shared_ptr<IIdentificator>> variables;
	for (const auto& [name, identificator] : m_identificators)
	{
		if (std::dynamic_pointer_cast<VariableIdentificator>(identificator))
		{
			variables.push_back(identificator);
		}
	}
	return variables;
}

std::vector<std::shared_ptr<IIdentificator>> IdentificatorRepository::getFunctions()
{
	std::vector<std::shared_ptr<IIdentificator>> functions;
	for (const auto& [name, identificator] : m_identificators)
	{
		if (std::dynamic_pointer_cast<FunctionIdentificator>(identificator))
		{
			functions.push_back(identificator);
		}
	}
	return functions;
}
