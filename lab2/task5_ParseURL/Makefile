make:
	g++ main.cpp ParseURL.cpp Utils/StringUtils.cpp -o ParseURL -std=c++20

unit_test:
	g++ ./Unit/ParseURLTest.cpp ParseURL.cpp Utils/StringUtils.cpp -o ParseURL_unit_tests -std=c++20
	./ParseURL_unit_tests
