#pragma once
#include "./Identificator.h"
#include <cmath>
#include <unordered_set>

class Variable : public Identificator
{
public:
	Variable(const std::string& name, double value = NAN);
	double GetValue() override;
	std::string GetName() const override;
	void SetValue(double newValue) override;
	void ResetCache() override;
	void AddDependent(Identificator* dependent) override;
	std::unordered_set<Identificator*> GetSubscribes() override;
	bool IsCacheValid() override;

private:
	std::string m_name;
	double m_value;
	std::unordered_set<Identificator*> m_dependents;
};