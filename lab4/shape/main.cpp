#include "stdafx.h"
#include "Shape.h"
#include "ShapeCreator.h"
#include "Canvas.h"

void Info(const std::vector<std::shared_ptr<CShape>> &shapes)
{
	for (const auto & shape : shapes)
	{
		std::cout << shape->ToString() << std::endl;
	}
}

int main()
{
	std::vector<std::shared_ptr<CShape>> shapes;
	std::ifstream input("input.txt");
	CShapeCreator shapeCreator(input);

	while (auto shape = shapeCreator.ExecuteCommand())
	{
		shapes.push_back(shape);
	}

	Info(shapes);


    return 0;
}

