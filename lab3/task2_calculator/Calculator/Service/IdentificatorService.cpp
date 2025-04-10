#include "./IdentificatorService.h"
#include "../Entity/FunctionIdentificator.h"
#include "../Entity/VariableIdentificator.h"
#include "../Exception/IdentificatorNameExistsException.h"
#include "../Exception/IdentificatorNotFoundException.h"
#include "../Exception/IdentificatorTypeNotIsVariableException.h"

IdentificatorService::IdentificatorService()
	: m_identificatorRepository(IdentificatorRepository())
{
}

void IdentificatorService::CreateFunctionIdentificator(const FunctionIdentificatorInput& functionIdentificatorInput)
{
	IdentificatorService::AssertIdentificatorNameNotExists(functionIdentificatorInput.identificatorName);
	auto leftIdentificator = this->m_identificatorRepository.GetIdentificatorByName(functionIdentificatorInput.firstIdentificatorName);
	IdentificatorService::AssertIdentificatorExists(leftIdentificator);

	IIdentificator* identificator;
	if (functionIdentificatorInput.operation)
	{
		auto rightIdentificator = this->m_identificatorRepository.GetIdentificatorByName(functionIdentificatorInput.secondIdentificatorName);
		IdentificatorService::AssertIdentificatorExists(rightIdentificator);
		identificator = new FunctionIdentificator(
			functionIdentificatorInput.identificatorName,
			leftIdentificator,
			*functionIdentificatorInput.operation,
			rightIdentificator);
	}
	else
	{
		identificator = new FunctionIdentificator(functionIdentificatorInput.identificatorName, leftIdentificator);
	}

	this->m_identificatorRepository.StoreIdentificator(identificator);
}

void IdentificatorService::CreateVariableIdentificator(const std::string& identificatorName)
{
	this->AssertIdentificatorNameNotExists(identificatorName);

	IIdentificator* newIdentificator = new VariableIdentificator(identificatorName);

	this->m_identificatorRepository.StoreIdentificator(newIdentificator);
}

void IdentificatorService::StoreVariableIdentificatorByValue(const std::string& identificatorName, double value)
{
	auto identificator = this->m_identificatorRepository.GetIdentificatorByName(identificatorName);

	if (!identificator)
	{
		identificator = new VariableIdentificator(identificatorName, value);
	}
	else
	{
		AssertIdentificatorIsVariable(identificator);
	}

	identificator->SetValue(value);

	this->m_identificatorRepository.StoreIdentificator(identificator);
}

void IdentificatorService::StoreVariableIdentificatorByIdentificator(const std::string& identificatorName, const std::string& identificatorValueName)
{
	auto identificator = this->m_identificatorRepository.GetIdentificatorByName(identificatorValueName);
	AssertIdentificatorExists(identificator);
	// AssertIdentificatorIsVariable(identificator);

	this->StoreVariableIdentificatorByValue(identificatorName, identificator->GetValue());
}

IdentificatorValueData IdentificatorService::GetIdentificatorValueData(const std::string identificatorName)
{
	auto identificator = this->m_identificatorRepository.GetIdentificatorByName(identificatorName);

	return IdentificatorValueData(identificatorName, identificator->GetValue());
}

std::vector<IdentificatorValueData> IdentificatorService::GetVariableIdentificatorValuesData()
{
	auto variableIdentificators = this->m_identificatorRepository.GetVariables();

	return IdentificatorService::CreateIdentificatorValuesData(variableIdentificators);
}

std::vector<IdentificatorValueData> IdentificatorService::GetFunctionIdentificatorValuesData()
{
	auto functionIdentificators = this->m_identificatorRepository.GetFunctions();

	return IdentificatorService::CreateIdentificatorValuesData(functionIdentificators);
}

std::vector<IdentificatorValueData> IdentificatorService::CreateIdentificatorValuesData(std::vector<IIdentificator*> identificators)
{
	std::vector<IdentificatorValueData> identificatorValues;

	for (const auto& identificator : identificators)
	{
		identificatorValues.push_back(IdentificatorValueData(identificator->GetName(), identificator->GetValue()));
	}

	return identificatorValues;
}

void IdentificatorService::AssertIdentificatorExists(IIdentificator* identificator)
{
	if (!identificator)
	{
		throw IdentificatorNotFoundException();
	}
}

void IdentificatorService::AssertIdentificatorIsVariable(IIdentificator* identificator)
{
	if (!dynamic_cast<VariableIdentificator*>(identificator))
	{
		throw IdentificatorTypeNotIsVariableException();
	}
}

void IdentificatorService::AssertIdentificatorNameNotExists(const std::string& identificatorName)
{
	auto identificator = this->m_identificatorRepository.GetIdentificatorByName(identificatorName);
	if (identificator)
	{
		throw IdentificatorNameExistsException();
	}
}