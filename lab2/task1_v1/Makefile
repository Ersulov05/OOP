make:
	g++ main.cpp Vector.cpp -o main -std=c++20

unit_test: make
	g++ ./Unit/VectorTest.cpp Vector.cpp -o vector_unit_tests -std=c++20
	./vector_unit_tests

test: make
	chmod +x ./tests/test.bash
	./tests/test.bash
