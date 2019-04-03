#include "stdafx.h"
#include "Triangle.h"
#include "SolidShape.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3,
	const uint32_t& outlineColor, const uint32_t& fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, CSolidShape(outlineColor, fillColor)
{
}

double CTriangle::GetArea() const
{
	double a = hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y);
	double b = hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y);
	double c = hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y);
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	double a = hypot(m_vertex1.x - m_vertex2.x, m_vertex1.y - m_vertex2.y);
	double b = hypot(m_vertex1.x - m_vertex3.x, m_vertex1.y - m_vertex3.y);
	double c = hypot(m_vertex3.x - m_vertex2.x, m_vertex3.y - m_vertex2.y);
	return a + b + c;
}

std::string CTriangle::ToString() const
{
	std::ostringstream str;
	str << std::fixed << std::setprecision(2);

	str << "Triangle:\n"
		<< "Vertex1 (" << m_vertex1.x << ", " << m_vertex1.y << ")\n"
		<< "Vertex2 (" << m_vertex2.x << ", " << m_vertex2.y << ")\n"
		<< "Vertex3 (" << m_vertex3.x << ", " << m_vertex3.y << ")\n"
		<< "Area: " << GetArea() << "\n"
		<< "Perimeter: " << GetPerimeter() << "\n"
		<< "Outline color: " << std::hex << GetOutlineColor() << "\n"
		<< "Fill color: " << std::hex << GetFillColor() << "\n";

	return str.str();
}

void CTriangle::Draw(ICanvas& canvas) const
{
	
}