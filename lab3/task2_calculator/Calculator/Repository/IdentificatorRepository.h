#pragma once
#include "../Entity/IIdentificator.h"
#include <string>
#include <unordered_map>
#include <vector>

class IdentificatorRepository
{
public:
	void StoreIdentificator(std::shared_ptr<IIdentificator> identificator);
	std::shared_ptr<IIdentificator> GetIdentificatorByName(const std::string& name);
	std::vector<std::shared_ptr<IIdentificator>> getVariables();
	std::vector<std::shared_ptr<IIdentificator>> getFunctions();

private:
	std::unordered_map<std::string, std::shared_ptr<IIdentificator>> m_identificators;
};