#pragma once
#include "../Entity/Identificator.h"
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

class IdentificatorRepository
{
public:
	IdentificatorRepository();
	void AddIdentificator(const Identificator& identificator);
	void StoreVariableIdentificator(const Identificator& identificator);
	std::optional<Identificator> GetIdentificatorByName(const std::string& identificatorName) const;
	std::unordered_map<std::string, Identificator> GetVariableIdentificators() const;
	std::unordered_map<std::string, Identificator> GetFunctionIdentificators() const;
	std::unordered_map<std::string, Identificator> GetAllIdentificators() const;

private:
	void AssertIdentificatorNameNotExists(const std::string& identificatorName);
	static void AssertIdentificatorTypeIsVariable(IdentificatorType identificatorType);

	std::unordered_map<std::string, Identificator> m_identificators;
};