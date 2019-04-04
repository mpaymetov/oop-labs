#include "stdafx.h"
#include "ShapeCreator.h"
#include "Circle.h"
#include "LineSegment.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Triangle.h"

CShapeCreator::CShapeCreator(std::istream& input)
	: m_actionMap({ { "line", std::bind(&CShapeCreator::CreateLine, this, std::placeholders::_1) },
		  { "triangle", std::bind(&CShapeCreator::CreateTriangle, this, std::placeholders::_1) },
		  { "rectangle", std::bind(&CShapeCreator::CreateRectangle, this, std::placeholders::_1) },
		  { "circle", std::bind(&CShapeCreator::CreateCircle, this, std::placeholders::_1) } })
	, m_input(input)
{
}

std::shared_ptr<IShape> CShapeCreator::ExecuteCommand() const
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string figure;
	strm >> figure;

	auto it = m_actionMap.find(figure);
	if (it != m_actionMap.end())
	{
		try
		{
			return it->second(strm);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return nullptr;
		}
	}

	return nullptr;
}

std::shared_ptr<IShape> CShapeCreator::CreateLine(std::istream& args) const
{
	CPoint startPoint, endPoint;
	std::string input;
	uint32_t outlineColor;

	args >> input;
	startPoint.x = std::stod(input);
	input.clear();
	args >> input;
	startPoint.y = std::stod(input);
	input.clear();

	args >> input;
	endPoint.x = std::stod(input);
	input.clear();
	args >> input;
	endPoint.y = std::stod(input);
	input.clear();

	args >> std::hex >> outlineColor;
	
	return std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}

std::shared_ptr<IShape> CShapeCreator::CreateTriangle(std::istream& args) const
{
	CPoint vertex1, vertex2, vertex3;
	std::string input;
	uint32_t outlineColor, fillColor;

	args >> input;
	vertex1.x = std::stod(input);
	input.clear();
	args >> input;
	vertex1.y = std::stod(input);
	input.clear();
	
	args >> input;
	vertex2.x = std::stod(input);
	input.clear();
	args >> input;
	vertex2.y = std::stod(input);
	input.clear();

	args >> input;
	vertex3.x = std::stod(input);
	input.clear();
	args >> input;
	vertex3.y = std::stod(input);

	args >> std::hex >> outlineColor;
	args >> std::hex >> fillColor;

	return std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

std::shared_ptr<IShape> CShapeCreator::CreateRectangle(std::istream& args) const
{
	CPoint leftTop;
	double wight, heigth;
	std::string input;
	uint32_t outlineColor, fillColor;

	args >> input;
	leftTop.x = std::stod(input);
	input.clear();
	args >> input;
	leftTop.y = std::stod(input);
	input.clear();

	args >> input;
	wight = std::stod(input);
	input.clear();
	args >> input;
	heigth = std::stod(input);

	args >> std::hex >> outlineColor;
	args >> std::hex >> fillColor;

	return std::make_shared<CRectangle>(leftTop, wight, heigth, outlineColor, fillColor);
}

std::shared_ptr<IShape> CShapeCreator::CreateCircle(std::istream& args) const
{
	CPoint center;
	double radius;
	std::string input;
	uint32_t outlineColor, fillColor;

	args >> input;
	center.x = std::stod(input);
	input.clear();
	args >> input;
	center.y = std::stod(input);
	input.clear();
	args >> input;
	radius = std::stod(input);

	args >> std::hex >> outlineColor;
	args >> std::hex >> fillColor;

	return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
}
