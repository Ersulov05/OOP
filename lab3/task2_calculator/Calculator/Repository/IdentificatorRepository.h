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
	std::vector<IIdentificator*> GetVariables();
	std::vector<IIdentificator*> GetFunctions();

private:
	std::unordered_map<std::string, IIdentificator*> m_identificators;
};