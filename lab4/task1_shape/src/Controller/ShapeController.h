#pragma once
#include "../Shape/Entity/CCircle.h"
#include "../Shape/Entity/CLineSegment.h"
#include "../Shape/Entity/CRectangle.h"
#include "../Shape/Entity/CTriangle.h"
#include "../Shape/Repository/ShapeRepository.h"
#include "../Utils/StringUtils.h"
#include "./ShapeCommand.h"
#include <iomanip>

#include "../Shape/Exception/InvalidCircleRadiusException.h"
#include "../Shape/Exception/InvalidRectangleSizeException.h"
#include "../Shape/Exception/InvalidTriangleException.h"
#include "../Utils/Exception/InvalidConvertStringToValueException.h"
#include "../Utils/Exception/ValueOutOfRangeException.h"
#include "./Exception/InvalidCountArgumentsException.h"
#include "./Exception/UnknownShapeCommandException.h"

const int PRECISION = 2;

class ShapeController
{
public:
	void HandleShapeCommand(const ShapeCommand& shapeCommand, std::ostream& output)
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

	void PrintAllShapes(std::ostream& output)
	{
		auto shapes = m_shapeRepository.GetAllShapes();
		output << "type : area : perimeter\n";
		for (const auto& shape : shapes)
		{
			ShapeController::PrintShape(output, shape);
		}
	}

	void PrintShapeWithMaxArea(std::ostream& output)
	{
		auto shape = m_shapeRepository.GetShapeWithMaxArea();
		if (shape)
		{
			output << "Shape with max area:\n";
			ShapeController::PrintShape(output, shape);
		}
	}

	void PrintShapeWithMinPerimeter(std::ostream& output)
	{
		auto shape = m_shapeRepository.GetShapeWithMinPerimeter();
		if (shape)
		{
			output << "Shape with min perimeter:\n";
			ShapeController::PrintShape(output, shape);
		}
	}

private:
	void ExecuteShapeCommand(const ShapeCommand& shapeCommand, std::ostream& output)
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
		default:
			throw UnknownShapeCommandException();
		}
	}

	void CreateLine(const ShapeCommand& shapeCommand)
	{
		ShapeController::AssertCorrectCountArguments(shapeCommand.stringArgs.size(), 4, 5);
		double x1 = GetValueByString(shapeCommand.stringArgs[0]);
		double y1 = GetValueByString(shapeCommand.stringArgs[1]);
		double x2 = GetValueByString(shapeCommand.stringArgs[2]);
		double y2 = GetValueByString(shapeCommand.stringArgs[3]);

		CLineSegment* line = new CLineSegment(
			CPoint(x1, y1),
			CPoint(x2, y2));

		m_shapeRepository.StoreShape(line);
	}

	void CreateRectangle(const ShapeCommand& shapeCommand)
	{
		ShapeController::AssertCorrectCountArguments(shapeCommand.stringArgs.size(), 4, 6);
		double x1 = GetValueByString(shapeCommand.stringArgs[0]);
		double y1 = GetValueByString(shapeCommand.stringArgs[1]);
		double x2 = GetValueByString(shapeCommand.stringArgs[2]);
		double y2 = GetValueByString(shapeCommand.stringArgs[3]);

		CRectangle* rectangle = new CRectangle(CPoint(x1, y1), CPoint(x2, y2));

		m_shapeRepository.StoreShape(rectangle);
	}

	void CreateTriangle(const ShapeCommand& shapeCommand)
	{
		ShapeController::AssertCorrectCountArguments(shapeCommand.stringArgs.size(), 6, 8);
		double x1 = GetValueByString(shapeCommand.stringArgs[0]);
		double y1 = GetValueByString(shapeCommand.stringArgs[1]);
		double x2 = GetValueByString(shapeCommand.stringArgs[2]);
		double y2 = GetValueByString(shapeCommand.stringArgs[3]);
		double x3 = GetValueByString(shapeCommand.stringArgs[4]);
		double y3 = GetValueByString(shapeCommand.stringArgs[5]);

		CTriangle* triangle = new CTriangle(
			CPoint(x1, y1),
			CPoint(x2, y2),
			CPoint(x3, y3));

		m_shapeRepository.StoreShape(triangle);
	}

	void CreateCircle(const ShapeCommand& shapeCommand)
	{
		ShapeController::AssertCorrectCountArguments(shapeCommand.stringArgs.size(), 3, 5);
		double x1 = GetValueByString(shapeCommand.stringArgs[0]);
		double y1 = GetValueByString(shapeCommand.stringArgs[1]);
		double radius = GetValueByString(shapeCommand.stringArgs[2]);

		CCircle* circle = new CCircle(
			CPoint(x1, y1),
			radius);

		m_shapeRepository.StoreShape(circle);
	}

	static void PrintShape(std::ostream& output, const IShape* shape)
	{
		output << std::fixed << std::setprecision(PRECISION);
		if (shape)
		{
			output << "Area: " << shape->GetArea() << " Perimeter: " << shape->GetPerimeter() << " " << shape->ToString(PRECISION) << std::endl;
		}
	}

	static void AssertCorrectCountArguments(int countArguments, int min, int max)
	{
		if (countArguments < min || countArguments > max)
		{
			throw InvalidCountArgumentsException();
		}
	}
	ShapeRepository m_shapeRepository;
};