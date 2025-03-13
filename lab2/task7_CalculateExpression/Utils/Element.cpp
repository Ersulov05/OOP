#include "Element.h"

Element CreateOpenBracketElement()
{
	Element element;
	element.type = ElementType::OPEN_BRACKET;
	return element;
}

Element CreateCloseBracketElement()
{
	Element element;
	element.type = ElementType::CLOSE_BRACKET;
	return element;
}

// TODO: Избавиться от перегрузки CreateElement
Element CreateElement(Operation operation) // TODO: паттерн фабричный метод
{
	Element element;
	element.type = ElementType::OPERATION;
	element.data.operation = operation;
	return element;
}

Element CreateElement(int value)
{
	Element element;
	element.type = ElementType::VALUE;
	element.data.value = value;
	return element;
}

Element CharToElement(char ch)
{
	switch (ch)
	{
	case '(': // TODO: Вынести в константы
		return CreateOpenBracketElement();
	case ')':
		return CreateCloseBracketElement();
	case '*':
		return CreateElement(Operation::MULTIPLY);
	case '+':
		return CreateElement(Operation::PLUS);
	default:
		throw InvalidSymbolInExpressionException(ch);
	}
}