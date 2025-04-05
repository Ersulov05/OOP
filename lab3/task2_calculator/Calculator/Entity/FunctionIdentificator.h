#pragma once
#include "./IIdentificator.h"
#include "./VariableIdentificator.h"
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>
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
		std::shared_ptr<IIdentificator> right)
		: m_name(name)
		, m_operation(ParseOperation(operation))
		, m_left(left.get())
		, m_right(right.get())
	{
		ValidateIdentifier(name);
		AddDependent(this);
	}

	FunctionIdentificator(const std::string& name,
		std::shared_ptr<IIdentificator> target)
		: m_name(name)
		, m_left(target.get())
	{
		ValidateIdentifier(name);
		AddDependent(this);
	}

	void AddDependent(IIdentificator* dependent) override
	{
		auto leftSubscribes = m_left->GetSubscribes();
		m_subscribes.insert(leftSubscribes.begin(), leftSubscribes.end());

		if (m_right)
		{
			auto rightSubscribes = m_right->GetSubscribes();
			m_subscribes.insert(rightSubscribes.begin(), rightSubscribes.end());
		}
		for (auto& subscribe : m_subscribes)
		{
			subscribe->AddDependent(dependent);
		}
	}

	std::unordered_set<IIdentificator*> GetSubscribes() override
	{
		return m_subscribes;
	}

	bool IsCacheValid() override
	{
		return m_cacheValid;
	}

	double GetValue() override
	{
		if (m_cacheValid)
		{
			return m_cachedValue;
		}
		std::stack<IIdentificator*> stack;
		stack.push(this);

		while (!stack.empty())
		{
			auto current = stack.top();

			if (current->IsCacheValid())
			{
				stack.pop();
				continue;
			}

			auto func = dynamic_cast<FunctionIdentificator*>(current);
			func->m_operation.has_value()
				? CalculateBinaryFunction(stack, func)
				: CalculateFunction(stack, func);
		}

		return m_cachedValue;
	}

	void SetCache(double value)
	{
		m_cachedValue = value;
		m_cacheValid = true;
	}

	std::string GetName() const override { return m_name; }

	void ResetCache() override
	{
		m_cacheValid = false;
	}

private:
	std::string m_name;
	std::optional<Operation> m_operation;
	IIdentificator* m_left = nullptr;
	IIdentificator* m_right = nullptr;
	mutable bool m_cacheValid = false;
	mutable double m_cachedValue = NAN;

	static Operation ParseOperation(const std::string& op)
	{
		if (op == "+")
			return Operation::PLUS;
		if (op == "-")
			return Operation::MINUS;
		if (op == "*")
			return Operation::MULTIPLY;
		if (op == "/")
			return Operation::DIVIDE;
		throw std::invalid_argument("Invalid operation: " + op);
	}

	static double ExecuteOperation(Operation operation, double a, double b)
	{
		switch (operation)
		{
		case Operation::PLUS:
			return a + b;
		case Operation::MINUS:
			return a - b;
		case Operation::MULTIPLY:
			return a * b;
		case Operation::DIVIDE:
			return b != 0
				? a / b
				: NAN;
		default:
			return NAN;
		}
	}

	void CalculateFunction(std::stack<IIdentificator*>& stack, FunctionIdentificator* func)
	{
		if (func->m_left->IsCacheValid())
		{
			func->SetCache(func->m_left->GetValue());
			stack.pop();
		}
		else
		{
			stack.push(func->m_left);
		}
		return;
	}

	void CalculateBinaryFunction(std::stack<IIdentificator*>& stack, FunctionIdentificator* func)
	{
		bool leftReady = func->m_left->IsCacheValid();
		bool rightReady = func->m_right->IsCacheValid();

		if (!rightReady)
			stack.push(func->m_right);
		if (!leftReady)
			stack.push(func->m_left);

		if (leftReady && rightReady)
		{
			double result = FunctionIdentificator::ExecuteOperation(
				*func->m_operation,
				func->m_left->GetValue(),
				func->m_right->GetValue());
			func->SetCache(result);
			stack.pop();
		}
	}

	std::unordered_set<IIdentificator*> m_subscribes;
};