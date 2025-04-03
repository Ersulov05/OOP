#include "./IdentificatorQueryService.h"
#include "../Exception/IdentificatorNotFoundException.h"

IdentificatorQueryService::IdentificatorQueryService(IdentificatorRepository& identificatorRepository)
	: m_identificatorRepository(identificatorRepository)
{
}

void IdentificatorQueryService::ClearCache()
{
	m_identificatorValuesCache.clear();
}

IdentificatorValueData IdentificatorQueryService::GetIdentificatorValueData(const std::string identificatorName)
{
	std::unordered_map<std::string, IdentificatorValueData> identificatorValues;
	float result = this->GetIdentificatorValueByIdentificatorName(identificatorName);

	return IdentificatorValueData(identificatorName, result);
}

std::vector<IdentificatorValueData> IdentificatorQueryService::GetVariableIdentificatorValuesData()
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
	std::vector<IdentificatorValueData> resultIdentificatorValues;
	std::unordered_map<std::string, Identificator> functionIdentificators = this->m_identificatorRepository.GetFunctionIdentificators();

	float result = 0;
	for (const auto& pairIdentificator : functionIdentificators)
	{
		result = this->GetIdentificatorValueByIdentificatorName(pairIdentificator.first);
		resultIdentificatorValues.push_back(IdentificatorValueData(pairIdentificator.first, result));
	}

	return resultIdentificatorValues;
}

float IdentificatorQueryService::GetIdentificatorValueByIdentificatorName(const std::string& identificatorName)
{
	std::optional<IdentificatorValueData> identificatorValueData = GetIdentificatorValueDataByCache(identificatorName);
	if (identificatorValueData)
	{
		return identificatorValueData->value;
	}

	std::optional<Identificator> identificator = m_identificatorRepository.GetIdentificatorByName(identificatorName);
	IdentificatorQueryService::AssertIdentificatorExists(identificator);

	float result = identificator->type == IdentificatorType::VARIABLE
		? identificator->data.value
		: CalculateFunction(*identificator->data.function);

	AddIdentificatorValueToCache(identificatorName, result);
	return result;
}

float IdentificatorQueryService::CalculateFunction(const Function& function)
{
	float firstArgument = this->GetIdentificatorValueByIdentificatorName(function.firstIdentificatorName);
	if (function.operation == Operation::NONE)
	{
		return firstArgument;
	}

	float secondArgument = this->GetIdentificatorValueByIdentificatorName(function.secondIdentificatorName);
	return ExecuteOperation(function.operation, firstArgument, secondArgument);
}

std::optional<IdentificatorValueData> IdentificatorQueryService::GetIdentificatorValueDataByCache(const std::string& identificatorName)
{
	auto it = m_identificatorValuesCache.find(identificatorName);
	if (it != m_identificatorValuesCache.end())
	{
		return it->second;
	}
	return std::nullopt;
}

void IdentificatorQueryService::AddIdentificatorValueToCache(const std::string& identificatorName, double value)
{
	m_identificatorValuesCache[identificatorName] = IdentificatorValueData(identificatorName, value);
}

void IdentificatorQueryService::AssertIdentificatorExists(std::optional<Identificator> identificator)
{
	if (!identificator)
	{
		throw IdentificatorNotFoundException();
	}
}