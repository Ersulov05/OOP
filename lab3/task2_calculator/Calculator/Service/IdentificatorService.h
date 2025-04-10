#pragma once
#include "../Repository/IdentificatorRepository.h"
#include "./Data/IdentificatorValueData.h"
#include "./Input/FunctionIdentificatorInput.h"
#include <string>

class IdentificatorService
{
public:
	explicit IdentificatorService();
	void CreateFunctionIdentificator(const FunctionIdentificatorInput& finctionIdentificatorInput);
	void CreateVariableIdentificator(const std::string& identificatorName);
	void StoreVariableIdentificatorByValue(const std::string& identificatorName, double value);
	void StoreVariableIdentificatorByIdentificator(const std::string& identificatorName, const std::string& identificatorValueName);

	IdentificatorValueData GetIdentificatorValueData(const std::string identificatorName);
	std::vector<IdentificatorValueData> GetVariableIdentificatorValuesData();
	std::vector<IdentificatorValueData> GetFunctionIdentificatorValuesData();

private:
	static std::vector<IdentificatorValueData> CreateIdentificatorValuesData(std::vector<Identificator*> identificators);
	static void AssertIdentificatorExists(Identificator* identificator);
	void AssertIdentificatorNameNotExists(const std::string& identificatorName);
	static void AssertIdentificatorIsVariable(Identificator* identificatorType);
	IdentificatorRepository m_identificatorRepository;
};