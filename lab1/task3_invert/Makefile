make:
	g++ Invert.cpp -o Invert -std=c++20

test_with_args: make
	chmod +x ./tests/testInvertWithArgs.bash
	./tests/testInvertWithArgs.bash

test_without_args: make
	chmod +x ./tests/testInvertWithoutArgs.bash
	./tests/testInvertWithoutArgs.bash

test: make
	chmod +x ./tests/testInvertWithArgs.bash
	./tests/testInvertWithArgs.bash
	echo
	chmod +x ./tests/testInvertWithoutArgs.bash
	./tests/testInvertWithoutArgs.bash

test4x4: make
	chmod +x ./tests/testInvertWithoutArgs4x4.bash
	./tests/testInvertWithoutArgs4x4.bash
