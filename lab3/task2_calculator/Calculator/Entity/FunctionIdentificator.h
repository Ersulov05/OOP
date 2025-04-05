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
		, m_left(left)
		, m_right(right)
	{
		ValidateIdentifier(name);
		// m_left->AddDependent(this);
		// if (m_right)
		// 	m_right->AddDependent(this);
		AddDependent(this);
	}

	FunctionIdentificator(const std::string& name,
		std::shared_ptr<IIdentificator> target)
		: m_name(name)
		, m_left(target)
	{
		ValidateIdentifier(name);
		AddDependent(this);
	}

	~FunctionIdentificator()
	{
		std::cout << "++";
		m_left = nullptr;
		m_right = nullptr;
		m_subscribes.clear();
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

	void RemoveDependencies() override
	{
		m_left = nullptr;
		m_right = nullptr;
		m_subscribes.clear();
	}

	bool IsCacheValid() override
	{
		return m_cacheValid;
	}

	double GetValue() override
	{
		if (m_cacheValid)
		{
			// std::cout << m_name << "cache" << std::endl;
			return m_cachedValue;
		}
		// std::cout << m_name << "-------cache------" << std::endl;
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

			if (!func->m_operation.has_value())
			{
				if (func->m_left->IsCacheValid())
				{
					func->SetCache(func->m_left->GetValue());
					stack.pop();
				}
				else
				{
					stack.push(func->m_left.get());
				}
				continue;
			}

			bool leftReady = func->m_left->IsCacheValid();
			bool rightReady = func->m_right->IsCacheValid();

			if (!rightReady)
				stack.push(func->m_right.get());
			if (!leftReady)
				stack.push(func->m_left.get());

			if (leftReady && rightReady)
			{
				double a = func->m_left->GetValue();
				double b = func->m_right->GetValue();
				double result = 0;
				switch (*func->m_operation)
				{
				case Operation::PLUS:
					result = a + b;
					break;
				case Operation::MINUS:
					result = a - b;
					break;
				case Operation::MULTIPLY:
					result = a * b;
					break;
				case Operation::DIVIDE:
					result = b != 0
						? a / b
						: NAN;
					break;
				}
				func->SetCache(result);
				stack.pop();
			}
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
	std::shared_ptr<IIdentificator> m_left;
	std::shared_ptr<IIdentificator> m_right;
	mutable bool m_cacheValid = false;
	mutable double m_cachedValue;

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
	std::unordered_set<IIdentificator*> m_subscribes;
};