#pragma once
#include "./IIdentificator.h"
#include <cmath>
#include <unordered_set>

class VariableIdentificator : public IIdentificator
{
public:
	VariableIdentificator(const std::string& name, double value = NAN);
	double GetValue() override;
	std::string GetName() const override;
	void SetValue(double newValue) override;
	void ResetCache() override;
	void AddDependent(IIdentificator* dependent) override;
	std::unordered_set<IIdentificator*> GetSubscribes() override;
	bool IsCacheValid() override;

private:
	std::string m_name;
	double m_value;
	std::unordered_set<IIdentificator*> m_dependents;
};