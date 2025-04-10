#include "./Variable.h"

Variable::Variable(const std::string& name, double value)
	: m_name(name)
	, m_value(value)
{
	ValidateName(name);
}

double Variable::GetValue()
{
	return m_value;
}

std::string Variable::GetName() const
{
	return m_name;
}

void Variable::SetValue(double newValue)
{
	m_value = newValue;
	ResetCache();
}

void Variable::ResetCache()
{
	for (auto& dependent : m_dependents)
	{
		if (dependent)
		{
			dependent->ResetCache();
		}
	}
}

void Variable::AddDependent(Identificator* dependent)
{
	if (dependent)
	{
		m_dependents.insert(dependent);
	}
}

std::unordered_set<Identificator*> Variable::GetSubscribes()
{
	return { this };
};

bool Variable::IsCacheValid()
{
	return true;
}