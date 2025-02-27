make:
	g++ main.cpp -o main -std=c++20

unit_test: make
	g++ vectorTest.cpp main.cpp ../../catch/catch.hpp -o unit -std=c++20

test: make
	chmod +x ./tests/test.bash
	./tests/test.bash
