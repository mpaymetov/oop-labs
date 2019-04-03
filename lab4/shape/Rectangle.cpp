#include "stdafx.h"
#include "Rectangle.h"
#include "SolidShape.h"

CRectangle::CRectangle(const CPoint& leftTop, const double& width, const double& height,
	const uint32_t& outlineColor, const uint32_t& fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, CSolidShape(outlineColor, fillColor)
{
}

double CRectangle::GetArea() const
{
	return (abs(m_width)) * (abs(m_height));
}

double CRectangle::GetPerimeter() const
{
	return 2 * (abs(m_width) + abs(m_height));
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

std::string CRectangle::ToString() const
{
	std::ostringstream str;
	str << std::fixed << std::setprecision(2);

	str << "Rectangle:\n"
		<< "LeftTop (" << m_leftTop.x << ", " << m_leftTop.y << ")\n"
		<< "Width: " << m_width << "\n"
		<< "Height: " << m_height << "\n"
		<< "Area: " << GetArea() << "\n"
		<< "Perimeter: " << GetPerimeter() << "\n"
		<< "Outline color: " << std::hex << GetOutlineColor() << "\n"
		<< "Fill color: " << std::hex << GetFillColor() << "\n";

	return str.str();
}

void CRectangle::Draw(ICanvas& canvas) const
{
}