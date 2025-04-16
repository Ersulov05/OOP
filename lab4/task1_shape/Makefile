# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude -Wno-unused-parameter
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

# Директории
SRC_DIR := src
TEST_DIR := Unit
BUILD_DIR := build
BIN_DIR := bin
TESTS_BIN_DIR := $(BIN_DIR)/tests

# Основные исходные файлы
MAIN_SRCS := \
	main.cpp \
	AppCommand.cpp \
	$(SRC_DIR)/Controller/ShapeCommand.cpp \
	$(SRC_DIR)/Controller/ShapeController.cpp \
	$(SRC_DIR)/Shape/Repository/ShapeRepository.cpp \
	$(SRC_DIR)/Shape/Entity/CCircle.cpp \
	$(SRC_DIR)/Shape/Entity/CRectangle.cpp \
	$(SRC_DIR)/Shape/Entity/CTriangle.cpp \
	$(SRC_DIR)/Shape/Entity/CLineSegment.cpp \
	$(SRC_DIR)/Canvas/CCanvas.cpp \

# Тестовые файлы
TEST_SRCS := \
	$(TEST_DIR)/Shape/Entity/CCircleTest.cpp \
	$(TEST_DIR)/Shape/Entity/CRectangleTest.cpp \
	$(TEST_DIR)/Shape/Repository/ShapeRepositoryTest.cpp

# Объектные файлы для основной программы
MAIN_OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(MAIN_SRCS))

# Генерация списка тестовых целей
TEST_TARGETS := $(patsubst $(TEST_DIR)/%.cpp,$(TESTS_BIN_DIR)/%_test,$(TEST_SRCS))

# Основная цель
all: $(BIN_DIR)/main

# Основная программа
$(BIN_DIR)/main: $(MAIN_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Правило для сборки тестов
$(TESTS_BIN_DIR)/%_test: $(BUILD_DIR)/$(TEST_DIR)/%.o $(filter-out $(BUILD_DIR)/main.o, $(MAIN_OBJS)) | $(TESTS_BIN_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Правило для объектных файлов основной программы
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для объектных файлов тестов
$(BUILD_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание основных директорий
$(BUILD_DIR) $(BIN_DIR) $(TESTS_BIN_DIR):
	mkdir -p $@

# Запуск всех тестов
test: $(TEST_TARGETS)
	@for test in $^; do \
		echo "Running $$test..."; \
		$$test && echo "$$test PASSED" || echo "$$test FAILED"; \
		echo; \
	done

# Очистка
clean:
	rm -rf ./$(BUILD_DIR) ./$(BIN_DIR)

.PHONY: all test clean