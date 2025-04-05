#pragma once
#include "./IIdentificator.h"
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

class FunctionIdentificator : public IIdentificator
{
public:
	FunctionIdentificator(const std::string& name, const std::string& operation,
		std::shared_ptr<IIdentificator> left,
		std::shared_ptr<IIdentificator> right);
	FunctionIdentificator(const std::string& name, std::shared_ptr<IIdentificator> target);
	void AddDependent(IIdentificator* dependent) override;
	std::unordered_set<IIdentificator*> GetSubscribes() override;
	bool IsCacheValid() override;
	double GetValue() override;
	void SetCache(double value);
	std::string GetName() const override;
	void ResetCache() override;

private:
	static Operation ParseOperation(const std::string& op);
	static double ExecuteOperation(Operation operation, double a, double b);
	void CalculateFunction(std::stack<IIdentificator*>& stack, FunctionIdentificator* func);
	void CalculateBinaryFunction(std::stack<IIdentificator*>& stack, FunctionIdentificator* func);

	std::string m_name;
	std::optional<Operation> m_operation;
	IIdentificator* m_left = nullptr;
	IIdentificator* m_right = nullptr;
	mutable bool m_cacheValid = false;
	mutable double m_cachedValue = NAN;
	std::unordered_set<IIdentificator*> m_subscribes;
};