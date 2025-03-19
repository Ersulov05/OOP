#include "../Repository/IdentificatorRepository.h"
#include "./Data/IdentificatorValueData.h"
#include <string>

class IdentificatorQueryService
{
public:
	IdentificatorQueryService(IdentificatorRepository& identificatorRepository);
	IdentificatorValueData GetIdentificatorValueData(const std::string identificatorName) const;
	Identificator GetIdentificator(const std::string identificatorName) const;
	std::vector<IdentificatorValueData> GetVariableIdentificatorValuesData() const;
	std::vector<IdentificatorValueData> GetFunctionIdentificatorValuesData() const;

private:
	IdentificatorRepository& identificatorRepository;
};