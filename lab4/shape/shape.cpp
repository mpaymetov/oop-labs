#include "stdafx.h"
#include "Shape.h"

CShape::CShape(const std::string& outlineColor)
	: m_outlineColor(outlineColor)
{}

std::string CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShape::SetOutlineColor(std::string const& color)
{
	m_outlineColor = color;
}

