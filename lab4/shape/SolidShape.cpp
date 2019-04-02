#include "stdafx.h"
#include "SolidShape.h"

CSolidShape::CSolidShape(const std::string& outlineColor, const std::string& fillColor) :
	m_fillColor(fillColor)
{
	SetOutlineColor(outlineColor);
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

void CSolidShape::SetFillColor(std::string const& color)
{
	m_fillColor = color;
}

