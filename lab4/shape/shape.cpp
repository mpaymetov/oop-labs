#include "stdafx.h"
#include "Shape.h"

CShape::CShape(const uint32_t outlineColor)
	: m_outlineColor(outlineColor)
{}

uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShape::SetOutlineColor(uint32_t const color)
{
	m_outlineColor = color;
}

std::string CShape::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(2);

	strm << GetType() << "\n"
		 << "Area: " << GetArea() << "\n"
		 << "Perimeter: " << GetPerimeter() << "\n"
		 << "Outline color: " << std::hex << GetOutlineColor() << "\n";
	AppendProperties(strm);

	return strm.str();
}

void CShape::AppendProperties(std::ostream& strm) const
{
}