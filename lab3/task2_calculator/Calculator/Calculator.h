#pragma once
#include "./Repository/IdentificatorRepository.h"
#include <string>
#include <unordered_map>
#include <vector>

struct IdentificatorValueData
{
	std::string identificatorName;
	double value;
};

class Calculator
{
public:
	Calculator();
	void AddIdentificator(Identificator identificator);
	double GetIdentificatorValue(std::string identificatorName) const;
	bool AreIdentificatorExists(std::string identificatorName) const;
	std::vector<> GetVariables() const;

private:
};