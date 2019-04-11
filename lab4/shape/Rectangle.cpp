#include "stdafx.h"
#include "Rectangle.h"
#include "SolidShape.h"

CRectangle::CRectangle(const CPoint& leftTop, const double width, const double height,
	const uint32_t outlineColor, const uint32_t fillColor)
	: CSolidShape(outlineColor, fillColor)
	, m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
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

std::string CRectangle::GetType() const
{
	return "Rectangle";
}

void CRectangle::AppendProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2);

	strm << "LeftTop (" << m_leftTop.x << ", " << m_leftTop.y << ")\n"
		 << "Width: " << m_width << "\n"
		 << "Height: " << m_height << "\n";

	return;
}

void CRectangle::Draw(ICanvas& canvas) const
{
}