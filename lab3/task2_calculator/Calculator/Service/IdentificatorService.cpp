#include "./IdentificatorService.h"
#include "../Exception/IdentificatorNotFoundException.h"

IdentificatorService::IdentificatorService(IdentificatorRepository& identificatorRepository)
	: m_identificatorRepository(identificatorRepository)
{
}

void IdentificatorService::CreateFunctionIdentificator(const FunctionIdentificatorInput& functionIdentificatorInput)
{
	std::optional<Identificator> firstIdentificator = this->m_identificatorRepository.GetIdentificatorByName(functionIdentificatorInput.firstIdentificatorName);
	IdentificatorService::AssertIdentificatorExists(firstIdentificator);
	if (functionIdentificatorInput.operation != Operation::NONE)
	{
		std::optional<Identificator> secondIdentificator = this->m_identificatorRepository.GetIdentificatorByName(functionIdentificatorInput.secondIdentificatorName);
		IdentificatorService::AssertIdentificatorExists(secondIdentificator);
	}

	Identificator newIdentificator;
	newIdentificator.name = functionIdentificatorInput.identificatorName;
	newIdentificator.type = IdentificatorType::FUNCTION;

	newIdentificator.data.function = new Function(functionIdentificatorInput.operation, functionIdentificatorInput.firstIdentificatorName, functionIdentificatorInput.secondIdentificatorName);
	this->m_identificatorRepository.AddIdentificator(newIdentificator);
}

void IdentificatorService::CreateVariableIdentificator(const std::string& identificatorName)
{
	Identificator newIdentificator;
	newIdentificator.name = identificatorName;
	newIdentificator.type = IdentificatorType::VARIABLE;
	this->m_identificatorRepository.AddIdentificator(newIdentificator);
}

void IdentificatorService::StoreVariableIdentificatorByValue(const std::string& identificatorName, double value)
{
	Identificator identificator;
	identificator.name = identificatorName;
	identificator.type = IdentificatorType::VARIABLE;
	identificator.data.value = value;

	this->m_identificatorRepository.StoreVariableIdentificator(identificator);
}

void IdentificatorService::StoreVariableIdentificatorByIdentificator(const std::string& identificatorName, const std::string& identificatorValueName)
{
	std::optional<Identificator> identificatorValue = this->m_identificatorRepository.GetIdentificatorByName(identificatorValueName);
	IdentificatorService::AssertIdentificatorExists(identificatorValue);
	IdentificatorService::AssertIdentificatorIsVariable(identificatorValue->type);

	this->StoreVariableIdentificatorByValue(identificatorName, identificatorValue->data.value);
}

void IdentificatorService::AssertIdentificatorExists(std::optional<Identificator> identificator)
{
	if (!identificator)
	{
		throw IdentificatorNotFoundException();
	}
}

void IdentificatorService::AssertIdentificatorIsVariable(IdentificatorType identificatorType)
{
	if (identificatorType != IdentificatorType::VARIABLE)
	{
		// error
	}
}