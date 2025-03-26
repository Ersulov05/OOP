#include "./IdentificatorQueryService.h"

IdentificatorQueryService::IdentificatorQueryService(IdentificatorRepository& identificatorRepository)
	: m_identificatorRepository(identificatorRepository)
{
}

IdentificatorValueData IdentificatorQueryService::GetIdentificatorValueData(const std::string identificatorName)
{
	std::unordered_map<std::string, IdentificatorValueData> identificatorValues;
	float result = this->GetIdentificatorValueByIdentificatorName(identificatorName, identificatorValues);

	return IdentificatorValueData(identificatorName, result);
}

std::vector<IdentificatorValueData> IdentificatorQueryService::GetVariableIdentificatorValuesData() const
{
	std::unordered_map<std::string, Identificator> variableIdentificators = this->m_identificatorRepository.GetVariableIdentificators();
	std::vector<IdentificatorValueData> identificatorValues;

	for (const auto& pairIdentificator : variableIdentificators)
	{
		auto identificator = pairIdentificator.second;
		identificatorValues.push_back(IdentificatorValueData(identificator.name, identificator.data.value));
	}

	return identificatorValues;
}

std::vector<IdentificatorValueData> IdentificatorQueryService::GetFunctionIdentificatorValuesData()
{
	std::unordered_map<std::string, IdentificatorValueData> identificatorValues;
	std::vector<IdentificatorValueData> resultIdentificatorValues;
	std::unordered_map<std::string, Identificator> functionIdentificators = this->m_identificatorRepository.GetFunctionIdentificators();

	float result = 0;
	for (const auto& pairIdentificator : functionIdentificators)
	{
		result = this->GetIdentificatorValueByIdentificatorName(pairIdentificator.first, identificatorValues);
		resultIdentificatorValues.push_back(IdentificatorValueData(pairIdentificator.first, result));
	}

	return resultIdentificatorValues;
}

float IdentificatorQueryService::GetIdentificatorValueByIdentificatorName(const std::string& identificatorName, std::unordered_map<std::string, IdentificatorValueData>& identificatorValues)
{
	std::optional<IdentificatorValueData> identificatorValueData = GetIdentificatorValueData(identificatorName, identificatorValues);
	if (identificatorValueData)
	{
		return identificatorValueData->value;
	}

	std::optional<Identificator> identificator = m_identificatorRepository.GetIdentificatorByName(identificatorName);
	IdentificatorQueryService::AssertIdentificatorExists(identificator);
	float result = 0;

	if (identificator->type == IdentificatorType::VARIABLE)
	{
		result = identificator->data.value;
	}
	else
	{
		result = CalculateFunction(*identificator->data.function, identificatorValues);
	}

	identificatorValues[identificatorName] = IdentificatorValueData(identificatorName, result);
	return result;
}

float IdentificatorQueryService::CalculateFunction(const Function& function, std::unordered_map<std::string, IdentificatorValueData>& identificatorValues)
{
	float firstArgument = this->GetIdentificatorValueByIdentificatorName(function.firstIdentificatorName, identificatorValues);
	if (function.operation == Operation::NONE)
	{
		return firstArgument;
	}

	float secondArgument = GetIdentificatorValueByIdentificatorName(function.secondIdentificatorName, identificatorValues);
	return this->ExecuteFunctionOperation(function.operation, firstArgument, secondArgument);
}

float IdentificatorQueryService::ExecuteFunctionOperation(Operation operation, float firstArgument, float secondArgument)
{
	switch (operation)
	{
	case Operation::PLUS:
		return firstArgument + secondArgument;
	case Operation::MINUS:
		return firstArgument - secondArgument;
	case Operation::MULTIPLY:
		return firstArgument * secondArgument;
	case Operation::DIVIDING:
		return firstArgument / secondArgument;
	default:
		return NAN;
	}
}

std::optional<IdentificatorValueData> IdentificatorQueryService::GetIdentificatorValueData(const std::string& identificatorName, const std::unordered_map<std::string, IdentificatorValueData>& identificatorValues)
{
	auto it = identificatorValues.find(identificatorName);
	if (it != identificatorValues.end())
	{
		return it->second;
	}
	return std::nullopt;
}

void IdentificatorQueryService::AssertIdentificatorExists(std::optional<Identificator> identificator)
{
	if (!identificator)
	{
		// error
	}
}