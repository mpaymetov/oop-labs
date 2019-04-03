#include "stdafx.h"
#include "Shape.h"
#include "ShapeCreator.h"
#include "Canvas.h"

void PrintShapesInfo(const std::vector<std::shared_ptr<CShape>> &shapes)
{
	for (const auto & shape : shapes)
	{
		std::cout << shape->ToString() << std::endl;
	}
}

std::vector<std::shared_ptr<CShape>> ReadShapes(std::ifstream& input)
{
	std::vector<std::shared_ptr<CShape>> shapes;
	CShapeCreator shapeCreator(input);
	while (auto shape = shapeCreator.ExecuteCommand())
	{
		shapes.push_back(shape);
	}
	return shapes;
}

std::shared_ptr<CShape> FindShapeWithMaxArea(const std::vector<std::shared_ptr<CShape>>& shapes)
{
	if (shapes.empty())
		return nullptr;
	auto max = std::max_element(shapes.begin(), shapes.end(),
		[](auto&& shape1, auto&& shape2) {
			return (shape1->GetArea() < shape2->GetArea());
		});
	return *max;
}

void PrintShapeWithMaxArea(const std::vector<std::shared_ptr<CShape>>& shapes)
{
	auto shapeWithMaxArea = FindShapeWithMaxArea(shapes);
	if (shapeWithMaxArea)
	{
		std::cout << "Shape with MAX area:\n" << shapeWithMaxArea->ToString() << "\n";
	}
}

std::shared_ptr<CShape> FindShapeWithMinPerimeter(const std::vector<std::shared_ptr<CShape>>& shapes)
{
	if (shapes.empty())
		return nullptr;
	auto min = std::min_element(shapes.begin(), shapes.end(),
		[](auto&& shape1, auto&& shape2) {
			return (shape1->GetPerimeter() < shape2->GetPerimeter());
		});
	return *min;
}

void PrintShapeWithMinPerimeter(const std::vector<std::shared_ptr<CShape>>& shapes)
{
	auto shapeWithMinPerimeter = FindShapeWithMinPerimeter(shapes);
	if (shapeWithMinPerimeter)
	{
		std::cout << "Shape with MIN perimeter:\n" << shapeWithMinPerimeter->ToString() << "\n";
	}
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n"
			 << "Usage: shape.exe <file with shapes>\n";
		return 1;
	}

	std::vector<std::shared_ptr<CShape>> shapes;
	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cout << "input file read error\n";
		return 1;
	}
	shapes = ReadShapes(input);

	if (shapes.empty())
	{
		std::cout << "no figure\n";
		return 0;
	}

	PrintShapesInfo(shapes);
	PrintShapeWithMaxArea(shapes);
	PrintShapeWithMinPerimeter(shapes);	

    return 0;
}

