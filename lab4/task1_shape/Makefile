make:
	g++ \
		main.cpp \
		AppCommand.cpp \
		src/Controller/ShapeCommand.cpp \
		src/Controller/ShapeController.cpp \
		src/Shape/Repository/ShapeRepository.cpp \
		src/Shape/Entity/CCircle.cpp \
		src/Shape/Entity/CRectangle.cpp \
		src/Shape/Entity/CTriangle.cpp \
		src/Shape/Entity/CLineSegment.cpp \
	-o main -std=c++20

unit_test:
	./src/Shape/Entity/CRectangle.cpp ./src/Shape/Entity/CTriangle.cpp ./src/Shape/Entity/CCircle.cpp ./src/Shape/Entity/CLineSegment.cpp