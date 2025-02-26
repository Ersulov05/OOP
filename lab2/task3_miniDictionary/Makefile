make:
	g++ MiniDictionary.cpp Utils/stringUtils.cpp -o MiniDictionary -std=c++20

test: make
	chmod +x ./tests/testHtmlDecoderWithArgs.bash
	./tests/testHtmlDecoderWithArgs.bash
