#pragma once
#include "../Repository/IdentificatorRepository.h"
#include "./Input/FunctionIdentificatorInput.h"
#include <string>

class IdentificatorService
{
public:
	explicit IdentificatorService(IdentificatorRepository& identificatorRepository);
	void CreateFunctionIdentificator(const FunctionIdentificatorInput& finctionIdentificatorInput);
	void CreateVariableIdentificator(const std::string& identificatorName);
	void StoreVariableIdentificatorByValue(const std::string& identificatorName, double value);
	void StoreVariableIdentificatorByIdentificator(const std::string& identificatorName, const std::string& identificatorValueName);

private:
	static void AssertIdentificatorExists(std::optional<Identificator> identificator);
	static void AssertIdentificatorIsVariable(IdentificatorType identificatorType);
	IdentificatorRepository& m_identificatorRepository;
};