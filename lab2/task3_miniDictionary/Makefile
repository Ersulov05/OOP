make:
	g++ main.cpp MiniDictionary.cpp Utils/StringUtils.cpp -o MiniDictionary -std=c++20

unit_test:
	g++ ./Unit/MiniDictionaryTest.cpp MiniDictionary.cpp Utils/StringUtils.cpp -o MiniDictionary_unit_tests -std=c++20
	./MiniDictionary_unit_tests

	g++ ./Unit/StringUtilsTest.cpp Utils/StringUtils.cpp -o StringUtils_unit_tests -std=c++20
	./StringUtils_unit_tests
