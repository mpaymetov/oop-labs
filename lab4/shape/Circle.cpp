#include "stdafx.h"
#include "Circle.h"
#include "SolidShape.h"

CCircle::CCircle(const CPoint& center, const double radius, const uint32_t outlineColor, const uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, CSolidShape(outlineColor, fillColor)
{}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::SetCenter(CPoint point)
{
	m_center = point;
}

void CCircle::SetRadius(double radius)
{
	m_radius = radius;
}

std::string CCircle::ToString() const
{
	std::ostringstream str;
	str << std::fixed << std::setprecision(2);

	str << "Circle:\n"
		<< "Center (" << m_center.x << ", " << m_center.y << ")\n"
		<< "Radius: " << GetRadius() << "\n"
		<< "Area: " << GetArea() << "\n"
		<< "Perimeter: " << GetPerimeter() << "\n"
		<< "Outline color: " << std::hex << GetOutlineColor() << "\n"
		<< "Fill color: " << std::hex << GetFillColor() << "\n";

	return str.str();
}

void CCircle::Draw(ICanvas& canvas) const
{
}