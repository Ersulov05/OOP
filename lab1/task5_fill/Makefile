make:
	g++ Fill.cpp -o Fill -std=c++20

test_with_args: make
	chmod +x ./tests/testFillWithArgs.bash
	./tests/testFillWithArgs.bash

test_without_args: make
	chmod +x ./tests/testFillWithoutArgs.bash
	./tests/testFillWithoutArgs.bash

test: make
	chmod +x ./tests/testFillWithArgs.bash
	./tests/testFillWithArgs.bash
	echo
	chmod +x ./tests/testFillWithoutArgs.bash
	./tests/testFillWithoutArgs.bash
