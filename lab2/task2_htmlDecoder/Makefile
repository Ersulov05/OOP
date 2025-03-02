make:
	g++ main.cpp HtmlDecoder.cpp -o HtmlDecoder -std=c++20

test: make
	chmod +x ./tests/testHtmlDecoderWithArgs.bash
	./tests/testHtmlDecoderWithArgs.bash

unit_test:
	g++ ./Unit/HtmlDecoderTest.cpp HtmlDecoder.cpp -o htmlDecoder_unit_tests -std=c++20
	./htmlDecoder_unit_tests
