#include "stdafx.h"
#include "SolidShape.h"

CSolidShape::CSolidShape(const uint32_t outlineColor, const uint32_t fillColor)
	:
	m_fillColor(fillColor)
{
	SetOutlineColor(outlineColor);
}

uint32_t CSolidShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CSolidShape::SetOutlineColor(uint32_t const color)
{
	m_outlineColor = color;
}

uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

void CSolidShape::SetFillColor(uint32_t const color)
{
	m_fillColor = color;
}

