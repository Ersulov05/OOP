#pragma once
#include "./Identificator.h"
#include <cmath>
#include <optional>
#include <string>
#include <unordered_set>

enum class Operation
{
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE
};

class Function : public Identificator
{
public:
	Function(const std::string& name,
		Identificator* left,
		const std::string& operation,
		Identificator* right);
	Function(const std::string& name, Identificator* target);
	void AddDependent(Identificator* dependent) override;
	std::unordered_set<Identificator*> GetSubscribes() override;
	bool IsCacheValid() override;
	double GetValue() override;
	void SetCache(double value);
	std::string GetName() const override;
	void ResetCache() override;

private:
	static Operation ParseOperation(const std::string& op);
	static double ExecuteOperation(Operation operation, double a, double b);
	void CalculateFunction(std::stack<Identificator*>& stack, Function* func);
	void CalculateBinaryFunction(std::stack<Identificator*>& stack, Function* func);

	std::string m_name;
	std::optional<Operation> m_operation;
	Identificator* m_left = nullptr;
	Identificator* m_right = nullptr;
	mutable bool m_cacheValid = false;
	mutable double m_cachedValue = NAN;
	std::unordered_set<Identificator*> m_subscribes;
};