#include "./Exception/InvalidExpressionException.h"
#include "./Exception/ValueInExpressionOutOfRangeException.h"
#include "./Exception/ValueOutOfRangeException.h"
#include "./Exception/ValueOutOfRangeWhenCalculatingException.h"
#include "./Utils/Element.h"
#include <optional>
#include <stack>
#include <vector>

std::vector<int> GetValues(std::stack<Element>& stack);

std::optional<Operation> GetOperation(std::stack<Element>& stack);

void ClearOpenBracket(std::stack<Element>& stack);

int GetSumm(const std::vector<int>& values);

int GetComposition(const std::vector<int>& values);

int Calculate(std::vector<int>& values, Operation operation);

int CalculateExpressionInStack(std::stack<Element>& stack);

Element GetElement(std::istream& input);