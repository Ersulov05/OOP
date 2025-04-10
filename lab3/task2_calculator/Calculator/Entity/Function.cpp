#include "./Function.h"
#include <stack>

Function::Function(const std::string& name,
	Identificator* left,
	const std::string& operation,
	Identificator* right)
	: m_name(name)
	, m_operation(ParseOperation(operation))
	, m_left(left)
	, m_right(right)
{
	ValidateName(name);
	AddDependent(this);
}

Function::Function(const std::string& name,
	Identificator* target)
	: m_name(name)
	, m_left(target)
{
	ValidateName(name);
	AddDependent(this);
}

void Function::AddDependent(Identificator* dependent)
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

std::unordered_set<Identificator*> Function::GetSubscribes()
{
	return m_subscribes;
}

bool Function::IsCacheValid()
{
	return m_cacheValid;
}

double Function::GetValue()
{
	if (m_cacheValid)
	{
		return m_cachedValue;
	}
	std::stack<Identificator*> stack;
	stack.push(this);

	while (!stack.empty())
	{
		auto current = stack.top();

		if (current->IsCacheValid())
		{
			stack.pop();
			continue;
		}

		auto func = dynamic_cast<Function*>(current);
		func->m_operation.has_value()
			? CalculateBinaryFunction(stack, func)
			: CalculateFunction(stack, func);
	}

	return m_cachedValue;
}

void Function::SetCache(double value)
{
	m_cachedValue = value;
	m_cacheValid = true;
}

std::string Function::GetName() const
{
	return m_name;
}

void Function::ResetCache()
{
	m_cacheValid = false;
}

Operation Function::ParseOperation(const std::string& operation)
{
	if (operation == "+")
		return Operation::PLUS;
	if (operation == "-")
		return Operation::MINUS;
	if (operation == "*")
		return Operation::MULTIPLY;
	if (operation == "/")
		return Operation::DIVIDE;
	throw std::invalid_argument("Invalid operation: " + operation);
}

double Function::ExecuteOperation(Operation operation, double a, double b)
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

void Function::CalculateFunction(std::stack<Identificator*>& stack, Function* func)
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

void Function::CalculateBinaryFunction(std::stack<Identificator*>& stack, Function* func)
{
	bool leftReady = func->m_left->IsCacheValid();
	bool rightReady = func->m_right->IsCacheValid();

	if (!rightReady)
		stack.push(func->m_right);
	if (!leftReady)
		stack.push(func->m_left);

	if (leftReady && rightReady)
	{
		double result = Function::ExecuteOperation(
			*func->m_operation,
			func->m_left->GetValue(),
			func->m_right->GetValue());
		func->SetCache(result);
		stack.pop();
	}
}