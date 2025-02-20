make:
	g++ Replace.cpp -o Replace -std=c++20

test_with_args: make
	./tests/testReplaceWithArgs.bash

test_without_args: make
	./tests/testReplace.bash

test: make
	./tests/testReplaceWithArgs.bash
	echo
	./tests/testReplace.bash
