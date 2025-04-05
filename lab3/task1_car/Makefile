make:
	g++ main.cpp AppCommand.cpp -o main -std=c++20

gear_unit_test:
	g++ ./Unit/GearTest.cpp ./Car/Transmission/Gear/Gear.cpp -o Gear_unit_tests -std=c++20
	./Gear_unit_tests

carController_unit_test:
	g++ ./Utils/ArgUtils.cpp ./Unit/CarControllerTest.cpp ./Controller/CarCommand.cpp ./Controller/CarController.cpp ./Car/Car.cpp ./Car/Transmission/Transmission.cpp ./Car/Direction.cpp ./Car/Transmission/Gear/Gear.cpp -o CarController_unit_tests -std=c++20
	./CarController_unit_tests

car_unit_test:
	g++ ./Unit/CarTest.cpp ./Car/Car.cpp ./Car/Transmission/Transmission.cpp ./Car/Direction.cpp ./Car/Transmission/Gear/Gear.cpp -o Car_unit_tests -std=c++20
	./Car_unit_tests

unit_test:
	g++ ./Unit/GearTest.cpp ./Car/Transmission/Gear/Gear.cpp -o Gear_unit_tests -std=c++20
	./Gear_unit_tests

	g++ ./Unit/TransmissionTest.cpp ./Car/Transmission/Transmission.cpp ./Car/Direction.cpp ./Car/Transmission/Gear/Gear.cpp -o Transmission_unit_tests -std=c++20
	./Transmission_unit_tests

	g++ ./Unit/CarTest.cpp ./Car/Car.cpp ./Car/Transmission/Transmission.cpp ./Car/Direction.cpp ./Car/Transmission/Gear/Gear.cpp -o Car_unit_tests -std=c++20
	./Car_unit_tests

	g++ ./Unit/AppCommandTest.cpp ./AppCommand.cpp -o AppCommand_unit_tests -std=c++20
	./AppCommand_unit_tests

	g++ ./Unit/CarCommandTest.cpp ./Controller/CarCommand.cpp -o CarCommand_unit_tests -std=c++20
	./CarCommand_unit_tests

	g++ ./Utils/ArgUtils.cpp ./Unit/CarControllerTest.cpp ./Controller/CarCommand.cpp ./Controller/CarController.cpp ./Car/Car.cpp ./Car/Transmission/Transmission.cpp ./Car/Direction.cpp ./Car/Transmission/Gear/Gear.cpp -o CarController_unit_tests -std=c++20
	./CarController_unit_tests