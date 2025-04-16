#pragma once
#include "../Shape/Repository/ShapeRepository.h"
#include "./ShapeCommand.h"

const int PRECISION = 2;

class ShapeController
{
public:
	void HandleShapeCommand(const ShapeCommand& shapeCommand, std::ostream& output);
	void PrintAllShapes(std::ostream& output);
	void PrintShapeWithMaxArea(std::ostream& output);
	void PrintShapeWithMinPerimeter(std::ostream& output);
	void RunWindow();

private:
	void ExecuteShapeCommand(const ShapeCommand& shapeCommand, std::ostream& output);
	void CreateLine(const ShapeCommand& shapeCommand);
	void CreateRectangle(const ShapeCommand& shapeCommand);
	void CreateTriangle(const ShapeCommand& shapeCommand);
	void CreateCircle(const ShapeCommand& shapeCommand);
	static void PrintShape(std::ostream& output, const IShape* shape);
	static void AssertCorrectCountArguments(int countArguments, int expected);
	ShapeRepository m_shapeRepository;
};