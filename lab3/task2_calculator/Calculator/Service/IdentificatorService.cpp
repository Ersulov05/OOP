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

	std::shared_ptr<IIdentificator> identificator;
	if (functionIdentificatorInput.operation)
	{
		auto rightIdentificator = this->m_identificatorRepository.GetIdentificatorByName(functionIdentificatorInput.secondIdentificatorName);
		IdentificatorService::AssertIdentificatorExists(rightIdentificator);
		identificator = std::make_shared<FunctionIdentificator>(
			functionIdentificatorInput.identificatorName,
			*functionIdentificatorInput.operation,
			leftIdentificator,
			rightIdentificator);
	}
	else
	{
		identificator = std::make_shared<FunctionIdentificator>(functionIdentificatorInput.identificatorName, leftIdentificator);
	}

	this->m_identificatorRepository.StoreIdentificator(identificator);
}

void IdentificatorService::CreateVariableIdentificator(const std::string& identificatorName)
{
	this->AssertIdentificatorNameNotExists(identificatorName);

	std::shared_ptr<IIdentificator> newIdentificator = std::make_shared<VariableIdentificator>(identificatorName);

	this->m_identificatorRepository.StoreIdentificator(newIdentificator);
}

void IdentificatorService::StoreVariableIdentificatorByValue(const std::string& identificatorName, double value)
{
	auto identificator = this->m_identificatorRepository.GetIdentificatorByName(identificatorName);

	if (!identificator)
	{
		identificator = std::make_shared<VariableIdentificator>(identificatorName, value);
	}
	identificator->SetValue(value);

	this->m_identificatorRepository.StoreIdentificator(identificator);
}

void IdentificatorService::StoreVariableIdentificatorByIdentificator(const std::string& identificatorName, const std::string& identificatorValueName)
{
	auto identificator = this->m_identificatorRepository.GetIdentificatorByName(identificatorValueName);
	AssertIdentificatorExists(identificator);
	AssertIdentificatorIsVariable(identificator);

	this->StoreVariableIdentificatorByValue(identificatorName, identificator->GetValue());
}

IdentificatorValueData IdentificatorService::GetIdentificatorValueData(const std::string identificatorName)
{
	auto identificator = this->m_identificatorRepository.GetIdentificatorByName(identificatorName);

	return IdentificatorValueData(identificatorName, identificator->GetValue());
}

std::vector<IdentificatorValueData> IdentificatorService::GetVariableIdentificatorValuesData()
{
	auto variableIdentificators = this->m_identificatorRepository.getVariables();

	return IdentificatorService::CreateIdentificatorValuesData(variableIdentificators);
}

std::vector<IdentificatorValueData> IdentificatorService::GetFunctionIdentificatorValuesData()
{
	auto functionIdentificators = this->m_identificatorRepository.getFunctions();

	return IdentificatorService::CreateIdentificatorValuesData(functionIdentificators);
}

std::vector<IdentificatorValueData> IdentificatorService::CreateIdentificatorValuesData(std::vector<std::shared_ptr<IIdentificator>> identificators)
{
	std::vector<IdentificatorValueData> identificatorValues;

	for (const auto& identificator : identificators)
	{
		identificatorValues.push_back(IdentificatorValueData(identificator->GetName(), identificator->GetValue()));
	}

	return identificatorValues;
}

void IdentificatorService::AssertIdentificatorExists(std::shared_ptr<IIdentificator> identificator)
{
	if (!identificator)
	{
		throw IdentificatorNotFoundException();
	}
}

void IdentificatorService::AssertIdentificatorIsVariable(std::shared_ptr<IIdentificator> identificator)
{
	if (!std::dynamic_pointer_cast<VariableIdentificator>(identificator))
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