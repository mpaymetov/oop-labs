#include "stdafx.h"
#include "LineSegment.h"

CLineSegment::CLineSegment(const CPoint& first, const CPoint& second, const uint32_t& color)
	:
	m_start(first),
	m_end(second),
	CShape(color)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return hypot(m_start.x - m_end.x, m_start.y - m_end.y);
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_end;
}

std::string CLineSegment::ToString() const
{
	std::ostringstream str;
	str << std::fixed << std::setprecision(2);

	str << "LineSegment:\n"
		<< "Start point (" << m_start.x << ", " << m_start.y << ")\n"
		<< "End point (" << m_end.x << ", " << m_end.y << ")\n"
		<< "Area: " << GetArea() << "\n"
		<< "Perimeter: " << GetPerimeter() << "\n"
		<< "Outline color: " << std::hex << GetOutlineColor() << "\n";

	return str.str();
}

void CLineSegment::Draw(ICanvas& canvas) const
{
}