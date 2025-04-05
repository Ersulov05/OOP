#include "./VariableIdentificator.h"

VariableIdentificator::VariableIdentificator(const std::string& name, double value)
	: m_name(name)
	, m_value(value)
{
	ValidateIdentifier(name);
}

double VariableIdentificator::GetValue()
{
	return m_value;
}

std::string VariableIdentificator::GetName() const
{
	return m_name;
}

void VariableIdentificator::SetValue(double newValue)
{
	m_value = newValue;
	ResetCache();
}

void VariableIdentificator::ResetCache()
{
	for (auto& dependent : m_dependents)
	{
		if (dependent)
		{
			dependent->ResetCache();
		}
	}
}

void VariableIdentificator::AddDependent(IIdentificator* dependent)
{
	if (dependent)
	{
		m_dependents.insert(dependent);
	}
}

std::unordered_set<IIdentificator*> VariableIdentificator::GetSubscribes()
{
	return { this };
};

bool VariableIdentificator::IsCacheValid()
{
	return true;
}