#include "../Repository/IdentificatorRepository.h"
#include <string>

enum class Operation;

struct FunctionIdentificatorInput
{
	std::string identificatorName;
	Operation operation;
	std::string firstIdentificatorName;
	std::string secondIdentificatorName;
};

struct VariableIdentificatorInput
{
	std::string identificatorName;
};

class IdentificatorService
{
public:
	void CreateFunctionIdentificator(const FunctionIdentificatorInput& finctionIdentificatorInput);
	void CreateVariableIdentificator(const std::string& identificatorName);
	void EditVariableIdentificator(const std::string& identificatorName, double value);
	void EditVariableIdentificator(const std::string& identificatorName, const std::string& identificatorValueName);

private:
	IdentificatorRepository identificatorRepository;
};