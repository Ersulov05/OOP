#pragma once
#include "../Entity/FunctionIdentificator.h"
#include "../Entity/IIdentificator.h"
#include "../Entity/VariableIdentificator.h"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

class IdentificatorRepository
{
public:
	IdentificatorRepository(){};
	~IdentificatorRepository()
	{
		for (auto& pair : m_identificators)
		{
			pair.second->RemoveDependencies();
		}
		m_identificators.clear();
	}
	void StoreIdentificator(std::shared_ptr<IIdentificator> identificator)
	{
		m_identificators[identificator->GetName()] = identificator;
	}

	std::shared_ptr<IIdentificator> GetIdentificatorByName(const std::string& name)
	{
		auto it = m_identificators.find(name);
		if (it == m_identificators.end())
		{
			return nullptr;
			// throw std::runtime_error("Identificator '" + name + "' not found");
		}
		return it->second;
	}

	std::vector<std::shared_ptr<IIdentificator>> getVariables()
	{
		std::vector<std::shared_ptr<IIdentificator>> variables;
		for (const auto& [name, identificator] : this->m_identificators)
		{
			if (std::dynamic_pointer_cast<VariableIdentificator>(identificator))
			{
				variables.push_back(identificator);
			}
		}
		return variables;
	}

	std::vector<std::shared_ptr<IIdentificator>> getFunctions()
	{
		std::vector<std::shared_ptr<IIdentificator>> functions;
		for (const auto& [name, identificator] : this->m_identificators)
		{
			if (std::dynamic_pointer_cast<FunctionIdentificator>(identificator))
			{
				functions.push_back(identificator);
			}
		}
		return functions;
	}

private:
	void AssertIdentificatorNameNotExists(const std::string& identificatorName) {};

	std::unordered_map<std::string, std::shared_ptr<IIdentificator>> m_identificators;
};