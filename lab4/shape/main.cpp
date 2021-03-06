#include "stdafx.h"
#include "Canvas.h"
#include "Shape.h"
#include "ShapeCreator.h"

void PrintShapesInfo(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	for (const auto& shape : shapes)
	{
		std::cout << shape->ToString() << std::endl;
	}
}

bool ReadShapesFromFile(std::string& inputFileName, std::vector<std::shared_ptr<IShape>>& shapes)
{
	if (inputFileName.empty())
	{
		std::cout << "input file name empty\n";
		return false;
	}

	std::ifstream input(inputFileName);
	if (!input.is_open())
	{
		std::cout << "input file read error\n";
		return false;
	}

	CShapeCreator shapeCreator(input);
	while (auto shape = shapeCreator.ExecuteCommand())
	{
		shapes.push_back(shape);
	}

	return true;
}

std::shared_ptr<IShape> FindShapeWithMaxArea(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	if (shapes.empty())
		return nullptr;
	auto max = std::max_element(shapes.begin(), shapes.end(),
		[](auto&& shape1, auto&& shape2) {
			return (shape1->GetArea() < shape2->GetArea());
		});
	return *max;
}

void PrintShapeWithMaxArea(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	auto shapeWithMaxArea = FindShapeWithMaxArea(shapes);
	if (shapeWithMaxArea)
	{
		std::cout << "Shape with MAX area:\n"
				  << shapeWithMaxArea->ToString() << "\n";
	}
}

std::shared_ptr<IShape> FindShapeWithMinPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	if (shapes.empty())
		return nullptr;
	auto min = std::min_element(shapes.begin(), shapes.end(),
		[](auto&& shape1, auto&& shape2) {
			return (shape1->GetPerimeter() < shape2->GetPerimeter());
		});
	return *min;
}

void PrintShapeWithMinPerimeter(const std::vector<std::shared_ptr<IShape>>& shapes)
{
	auto shapeWithMinPerimeter = FindShapeWithMinPerimeter(shapes);
	if (shapeWithMinPerimeter)
	{
		std::cout << "Shape with MIN perimeter:\n"
				  << shapeWithMinPerimeter->ToString() << "\n";
	}
}

std::string ParseCommandLine(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage: shape.exe <file with shapes>\n";
		return "";
	}

	return argv[1];
}

void DrawToFile(std::vector<std::shared_ptr<IShape>> shapes, std::string const& fileName)
{
	CCanvas canvas(fileName);
	for (const auto& shape : shapes)
	{
		shape->Draw(canvas);
	}
}

int main(int argc, char* argv[])
{
	std::string inputFileName = ParseCommandLine(argc, argv);
	std::vector<std::shared_ptr<IShape>> shapes;

	if (!ReadShapesFromFile(inputFileName, shapes))
	{
		return 1;
	}

	if (shapes.empty())
	{
		std::cout << "no figure\n";
		return 0;
	}

	PrintShapesInfo(shapes);
	PrintShapeWithMaxArea(shapes);
	PrintShapeWithMinPerimeter(shapes);

	DrawToFile(shapes, "example.svg");

	return 0;
}
