#pragma once
#include "../Entity/IIdentificator.h"
#include <string>
#include <unordered_map>
#include <vector>

class IdentificatorRepository
{
public:
	~IdentificatorRepository();
	void StoreIdentificator(IIdentificator* identificator);
	IIdentificator* GetIdentificatorByName(const std::string& name);
	std::vector<IIdentificator*> getVariables();
	std::vector<IIdentificator*> getFunctions();

private:
	std::unordered_map<std::string, IIdentificator*> m_identificators;
};