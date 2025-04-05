#pragma once
#include "./IIdentificator.h"
#include <cmath>
#include <iostream>
#include <unordered_set>

class VariableIdentificator : public IIdentificator
{
public:
	VariableIdentificator(const std::string& name, double value = NAN)
		: m_name(name)
		, m_value(value)
	{
		ValidateIdentifier(name);
	}

	double GetValue() override { return m_value; }
	std::string GetName() const override { return m_name; }
	void SetValue(double newValue) override
	{
		m_value = newValue;
		ResetCache();
	}

	void ResetCache() override
	{
		for (auto& dependent : m_dependents)
		{
			if (dependent)
			{
				dependent->ResetCache();
			}
		}
	}

	void AddDependent(IIdentificator* dependent) override
	{
		if (dependent)
		{
			m_dependents.insert(dependent);
		}
	}

	virtual std::unordered_set<IIdentificator*> GetSubscribes() override
	{
		return { this };
	};

	bool IsCacheValid() override
	{
		return true;
	}

private:
	std::string m_name;
	double m_value;
	std::unordered_set<IIdentificator*> m_dependents;
};