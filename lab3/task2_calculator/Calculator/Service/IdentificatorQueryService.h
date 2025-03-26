#include "../Repository/IdentificatorRepository.h"
#include "./Data/IdentificatorValueData.h"
#include <string>

class IdentificatorQueryService
{
public:
	IdentificatorQueryService(IdentificatorRepository& identificatorRepository);
	IdentificatorValueData GetIdentificatorValueData(const std::string identificatorName);
	// Identificator GetIdentificator(const std::string identificatorName) const;
	std::vector<IdentificatorValueData> GetVariableIdentificatorValuesData() const;
	std::vector<IdentificatorValueData> GetFunctionIdentificatorValuesData();

private:
	float GetIdentificatorValueByIdentificatorName(const std::string& identificatorName, std::unordered_map<std::string, IdentificatorValueData>& identificatorValues);
	std::optional<IdentificatorValueData> GetIdentificatorValueData(const std::string& identificatorName, const std::unordered_map<std::string, IdentificatorValueData>& identificatorValues);
	float CalculateFunction(const Function& function, std::unordered_map<std::string, IdentificatorValueData>& identificatorValues);
	float ExecuteFunctionOperation(Operation operation, float firstArgument, float secondArgument);
	static void AssertIdentificatorExists(std::optional<Identificator> identificator);
	IdentificatorRepository& m_identificatorRepository;
};