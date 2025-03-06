make:
	g++ main.cpp CalculateExpression.cpp ./Utils/Element.cpp ./Utils/NumberUtils.cpp -o CalculateExpression -std=c++20

unit_test:
	g++ ./Unit/CalculateExpressionTest.cpp CalculateExpression.cpp ./Utils/Element.cpp ./Utils/NumberUtils.cpp -o CalculateExpression_unit_tests -std=c++20
	./CalculateExpression_unit_tests
	g++ ./Unit/ElementTest.cpp ./Utils/Element.cpp ./Utils/NumberUtils.cpp -o ElementTest_unit_tests -std=c++20
	./ElementTest_unit_tests
