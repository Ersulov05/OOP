make:
	g++ Replace.cpp -o Replace -std=c++20

test_with_args: make
	chmod +x ./tests/testReplaceWithArgs.bash
	./tests/testReplaceWithArgs.bash

test_without_args: make
	chmod +x ./tests/testReplace.bash
	./tests/testReplace.bash

test: make
	chmod +x ./tests/testReplaceWithArgs.bash
	./tests/testReplaceWithArgs.bash
	echo
	chmod +x ./tests/testReplace.bash
	./tests/testReplace.bash
