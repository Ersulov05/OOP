#pragma once
#include "../Repository/IdentificatorRepository.h"
#include "./Data/IdentificatorValueData.h"
#include <string>

class IdentificatorQueryService
{
public:
	explicit IdentificatorQueryService(IdentificatorRepository& identificatorRepository);
	IdentificatorValueData GetIdentificatorValueData(const std::string identificatorName);
	std::vector<IdentificatorValueData> GetVariableIdentificatorValuesData() const;
	std::vector<IdentificatorValueData> GetFunctionIdentificatorValuesData();
	void ClearCache();

private:
	float GetIdentificatorValueByIdentificatorName(const std::string& identificatorName);
	std::optional<IdentificatorValueData> GetIdentificatorValueDataByCache(const std::string& identificatorName);
	void AddIdentificatorValueToCache(const std::string& identificatorName, double value);
	float CalculateFunction(const Function& function);
	static void AssertIdentificatorExists(std::optional<Identificator> identificator);

	IdentificatorRepository& m_identificatorRepository;
	std::unordered_map<std::string, IdentificatorValueData> m_identificatorValuesCache;
};