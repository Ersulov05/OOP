#include "../Repository/IdentificatorRepository.h"
#include <string>

struct FunctionIdentificatorInput
{
	std::string identificatorName;
	Operation operation;
	std::string firstIdentificatorName;
	std::string secondIdentificatorName;

	FunctionIdentificatorInput(std::string identificatorName, Operation operation, std::string firstIdentificatorName, std::string secondIdentificatorName = "")
		: identificatorName(identificatorName)
		, operation(operation)
		, firstIdentificatorName(firstIdentificatorName)
		, secondIdentificatorName(secondIdentificatorName){};
};

class IdentificatorService
{
public:
	IdentificatorService(IdentificatorRepository& identificatorRepository);
	void CreateFunctionIdentificator(const FunctionIdentificatorInput& finctionIdentificatorInput);
	void CreateVariableIdentificator(const std::string& identificatorName);
	void EditVariableIdentificatorByValue(const std::string& identificatorName, double value);
	void EditVariableIdentificatorByIdentificator(const std::string& identificatorName, const std::string& identificatorValueName);

private:
	static void AssertIdentificatorExists(std::optional<Identificator> identificator);
	static void AssertIdentificatorIsVariable(IdentificatorType identificatorType);
	IdentificatorRepository& m_identificatorRepository;
};