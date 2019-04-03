#include "stdafx.h"
#include "Shape.h"

CShape::CShape(const uint32_t& outlineColor)
	: m_outlineColor(outlineColor)
{}

uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShape::SetOutlineColor(uint32_t const& color)
{
	m_outlineColor = color;
}

