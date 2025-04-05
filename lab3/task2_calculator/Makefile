make:
	g++ main.cpp ./AppCommand.cpp ./Controller/CalculatorCommand.cpp ./Controller/CalculatorController.cpp ./Calculator/Service/IdentificatorService.cpp ./Calculator/Service/IdentificatorQueryService.cpp ./Calculator/Repository/IdentificatorRepository.cpp ./Calculator/Entity/Operation.cpp -o main -std=c++20

make_v2:
	g++ main.cpp ./Controller/CalculatorController.cpp ./Calculator/Service/IdentificatorService.cpp ./Controller/CalculatorCommand.cpp ./AppCommand.cpp ./Calculator/Repository/IdentificatorRepository.cpp ./Calculator/Entity/FunctionIdentificator.cpp ./Calculator/Entity/VariableIdentificator.cpp -o main

unit_test:
	g++ ./Unit/IdentificatorServiceTest.cpp ./Calculator/Service/IdentificatorService.cpp ./Calculator/Service/IdentificatorQueryService.cpp ./Calculator/Repository/IdentificatorRepository.cpp ./Calculator/Entity/Operation.cpp -o IdentificatorService_unit_tests -std=c++20
	./IdentificatorService_unit_tests
	g++ ./Unit/IdentificatorQueryServiceTest.cpp ./Calculator/Service/IdentificatorService.cpp ./Calculator/Service/IdentificatorQueryService.cpp ./Calculator/Repository/IdentificatorRepository.cpp ./Calculator/Entity/Operation.cpp -o IdentificatorQueryService_unit_tests -std=c++20
	./IdentificatorQueryService_unit_tests
	g++ ./Unit/OperationTest.cpp ./Calculator/Entity/Operation.cpp -o Operation_unit_tests -std=c++20
	./Operation_unit_tests
	g++ ./Unit/CalculatorControllerTest.cpp ./Controller/CalculatorCommand.cpp ./Controller/CalculatorController.cpp ./Calculator/Service/IdentificatorService.cpp ./Calculator/Service/IdentificatorQueryService.cpp ./Calculator/Repository/IdentificatorRepository.cpp ./Calculator/Entity/Operation.cpp -o CalculatorController_unit_tests -std=c++20
	./CalculatorController_unit_tests
	