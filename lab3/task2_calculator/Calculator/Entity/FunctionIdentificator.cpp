#include "./FunctionIdentificator.h"
#include <stack>

FunctionIdentificator::FunctionIdentificator(const std::string& name, const std::string& operation,
	IIdentificator* left,
	IIdentificator* right)
	: m_name(name)
	, m_operation(ParseOperation(operation))
	, m_left(left)
	, m_right(right)
{
	ValidateIdentifier(name);
	AddDependent(this);
}

FunctionIdentificator::FunctionIdentificator(const std::string& name,
	IIdentificator* target)
	: m_name(name)
	, m_left(target)
{
	ValidateIdentifier(name);
	AddDependent(this);
}

void FunctionIdentificator::AddDependent(IIdentificator* dependent)
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

std::unordered_set<IIdentificator*> FunctionIdentificator::GetSubscribes()
{
	return m_subscribes;
}

bool FunctionIdentificator::IsCacheValid()
{
	return m_cacheValid;
}

double FunctionIdentificator::GetValue()
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

void FunctionIdentificator::SetCache(double value)
{
	m_cachedValue = value;
	m_cacheValid = true;
}

std::string FunctionIdentificator::GetName() const
{
	return m_name;
}

void FunctionIdentificator::ResetCache()
{
	m_cacheValid = false;
}

Operation FunctionIdentificator::ParseOperation(const std::string& operation)
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

double FunctionIdentificator::ExecuteOperation(Operation operation, double a, double b)
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

void FunctionIdentificator::CalculateFunction(std::stack<IIdentificator*>& stack, FunctionIdentificator* func)
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

void FunctionIdentificator::CalculateBinaryFunction(std::stack<IIdentificator*>& stack, FunctionIdentificator* func)
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