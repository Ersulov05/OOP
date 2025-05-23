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
	static std::vector<IdentificatorValueData> CreateIdentificatorValuesData(std::vector<std::shared_ptr<IIdentificator>> identificators);
	static void AssertIdentificatorExists(std::shared_ptr<IIdentificator> identificator);
	void AssertIdentificatorNameNotExists(const std::string& identificatorName);
	static void AssertIdentificatorIsVariable(std::shared_ptr<IIdentificator> identificatorType);
	IdentificatorRepository m_identificatorRepository;
};