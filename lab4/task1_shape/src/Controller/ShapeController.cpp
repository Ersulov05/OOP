#include "../Canvas/CCanvas.h"
#include "../Shape/Exception/InvalidCircleRadiusException.h"
#include "../Shape/Exception/InvalidRectangleSizeException.h"
#include "../Shape/Exception/InvalidTriangleException.h"
#include "../Utils/Exception/InvalidConvertStringToValueException.h"
#include "../Utils/Exception/ValueOutOfRangeException.h"
#include "./Exception/InvalidCountArgumentsException.h"
#include "./Exception/UnknownShapeCommandException.h"

#include "../Shape/Entity/CCircle.h"
#include "../Shape/Entity/CLineSegment.h"
#include "../Shape/Entity/CRectangle.h"
#include "../Shape/Entity/CTriangle.h"
#include "../Utils/StringUtils.h"
#include "./ShapeController.h"

void ShapeController::HandleShapeCommand(const ShapeCommand& shapeCommand, std::ostream& output)
{
	try
	{
		ExecuteShapeCommand(shapeCommand, output);
	}
	catch (InvalidCircleRadiusException& e)
	{
		output << e.what() << std::endl;
	}
	catch (InvalidRectangleSizeException& e)
	{
		output << e.what() << std::endl;
	}
	catch (InvalidTriangleException& e)
	{
		output << e.what() << std::endl;
	}
	catch (InvalidConvertStringToValueException& e)
	{
		output << e.what() << std::endl;
	}
	catch (ValueOutOfRangeException& e)
	{
		output << e.what() << std::endl;
	}
	catch (InvalidCountArgumentsException& e)
	{
		output << e.what() << std::endl;
	}
	catch (std::runtime_error& e)
	{
		output << e.what() << std::endl;
	}
}

void ShapeController::PrintAllShapes(std::ostream& output)
{
	auto shapes = m_shapeRepository.GetAllShapes();
	output << "type : area : perimeter\n";
	for (const auto& shape : shapes)
	{
		ShapeController::PrintShape(output, shape);
	}
}

void ShapeController::PrintShapeWithMaxArea(std::ostream& output)
{
	auto shape = m_shapeRepository.GetShapeWithMaxArea();
	if (shape)
	{
		output << "Shape with max area:\n";
		ShapeController::PrintShape(output, shape);
	}
}

void ShapeController::PrintShapeWithMinPerimeter(std::ostream& output)
{
	auto shape = m_shapeRepository.GetShapeWithMinPerimeter();
	if (shape)
	{
		output << "Shape with min perimeter:\n";
		ShapeController::PrintShape(output, shape);
	}
}

void ShapeController::RunWindow()
{
	auto shapes = m_shapeRepository.GetAllShapes();
	CCanvas canvas(800, 600);
	while (canvas.IsOpen())
	{
		canvas.ProcessEvents();

		canvas.Clear(0x000000ff);

		for (auto shape : shapes)
		{
			shape->Draw(canvas);
		}

		canvas.Display();
	}
}

void ShapeController::ExecuteShapeCommand(const ShapeCommand& shapeCommand, std::ostream& output)
{
	switch (shapeCommand.type)
	{
	case ShapeCommandType::LINE:
		CreateLine(shapeCommand);
		break;
	case ShapeCommandType::RECTANGLE:
		CreateRectangle(shapeCommand);
		break;
	case ShapeCommandType::TRIANGLE:
		CreateTriangle(shapeCommand);
		break;
	case ShapeCommandType::CIRCLE:
		CreateCircle(shapeCommand);
		break;
	case ShapeCommandType::SHAPE_WITH_MAX_AREA:
		PrintShapeWithMaxArea(output);
		break;
	case ShapeCommandType::SHAPE_WITH_MIN_PERIMETER:
		PrintShapeWithMinPerimeter(output);
		break;
	case ShapeCommandType::PRINT_ALL:
		PrintAllShapes(output);
		break;
	case ShapeCommandType::RUN_WINDOW:
		RunWindow();
		break;
	default:
		throw UnknownShapeCommandException();
	}
}

void ShapeController::CreateLine(const ShapeCommand& shapeCommand)
{
	ShapeController::AssertCorrectCountArguments(shapeCommand.stringArgs.size(), 5);
	double x1 = GetDoubleValueByString(shapeCommand.stringArgs[0]);
	double y1 = GetDoubleValueByString(shapeCommand.stringArgs[1]);
	double x2 = GetDoubleValueByString(shapeCommand.stringArgs[2]);
	double y2 = GetDoubleValueByString(shapeCommand.stringArgs[3]);
	u_int32_t outlineColor = GetUIntValueByString(shapeCommand.stringArgs[4]);

	CLineSegment* line = new CLineSegment(CPoint(x1, y1), CPoint(x2, y2), outlineColor);

	m_shapeRepository.StoreShape(line);
}

void ShapeController::CreateRectangle(const ShapeCommand& shapeCommand)
{
	ShapeController::AssertCorrectCountArguments(shapeCommand.stringArgs.size(), 6);
	double x1 = GetDoubleValueByString(shapeCommand.stringArgs[0]);
	double y1 = GetDoubleValueByString(shapeCommand.stringArgs[1]);
	double x2 = GetDoubleValueByString(shapeCommand.stringArgs[2]);
	double y2 = GetDoubleValueByString(shapeCommand.stringArgs[3]);
	u_int32_t outlineColor = GetUIntValueByString(shapeCommand.stringArgs[4]);
	u_int32_t fillColor = GetUIntValueByString(shapeCommand.stringArgs[5]);

	CRectangle* rectangle = new CRectangle(CPoint(x1, y1), CPoint(x2, y2), outlineColor, fillColor);

	m_shapeRepository.StoreShape(rectangle);
}

void ShapeController::CreateTriangle(const ShapeCommand& shapeCommand)
{
	ShapeController::AssertCorrectCountArguments(shapeCommand.stringArgs.size(), 8);
	double x1 = GetDoubleValueByString(shapeCommand.stringArgs[0]);
	double y1 = GetDoubleValueByString(shapeCommand.stringArgs[1]);
	double x2 = GetDoubleValueByString(shapeCommand.stringArgs[2]);
	double y2 = GetDoubleValueByString(shapeCommand.stringArgs[3]);
	double x3 = GetDoubleValueByString(shapeCommand.stringArgs[4]);
	double y3 = GetDoubleValueByString(shapeCommand.stringArgs[5]);
	u_int32_t outlineColor = GetUIntValueByString(shapeCommand.stringArgs[6]);
	u_int32_t fillColor = GetUIntValueByString(shapeCommand.stringArgs[7]);

	CTriangle* triangle = new CTriangle(
		CPoint(x1, y1),
		CPoint(x2, y2),
		CPoint(x3, y3),
		outlineColor,
		fillColor);

	m_shapeRepository.StoreShape(triangle);
}

void ShapeController::CreateCircle(const ShapeCommand& shapeCommand)
{
	ShapeController::AssertCorrectCountArguments(shapeCommand.stringArgs.size(), 5);
	double x1 = GetDoubleValueByString(shapeCommand.stringArgs[0]);
	double y1 = GetDoubleValueByString(shapeCommand.stringArgs[1]);
	double radius = GetDoubleValueByString(shapeCommand.stringArgs[2]);
	u_int32_t outlineColor = GetUIntValueByString(shapeCommand.stringArgs[3]);
	u_int32_t fillColor = GetUIntValueByString(shapeCommand.stringArgs[4]);

	CCircle* circle = new CCircle(
		CPoint(x1, y1),
		radius,
		outlineColor,
		fillColor);

	m_shapeRepository.StoreShape(circle);
}

void ShapeController::PrintShape(std::ostream& output, const IShape* shape)
{
	output << std::fixed << std::setprecision(PRECISION);
	if (shape)
	{
		output << shape->ToString(PRECISION) << std::endl;
	}
}

void ShapeController::AssertCorrectCountArguments(int countArguments, int expected)
{
	if (countArguments != expected)
	{
		throw InvalidCountArgumentsException();
	}
}