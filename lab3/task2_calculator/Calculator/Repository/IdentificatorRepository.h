#pragma once
#include "../Entity/Identificator.h"
#include <string>
#include <unordered_map>
#include <vector>

class IdentificatorRepository
{
public:
	~IdentificatorRepository();
	void StoreIdentificator(Identificator* identificator);
	Identificator* GetIdentificatorByName(const std::string& name);
	std::vector<Identificator*> GetVariables();
	std::vector<Identificator*> GetFunctions();

private:
	std::unordered_map<std::string, Identificator*> m_identificators;
};