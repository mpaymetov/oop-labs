#include "stdafx.h"
#include "LineSegment.h"

CLineSegment::CLineSegment(const CPoint& first, const CPoint& second, const uint32_t color)
	: CShape(color)
	, m_start(first)
	, m_end(second)
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

std::string CLineSegment::GetType() const
{
	return "LineSegment";
}

void CLineSegment::AppendProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2);
	strm << "Start point (" << m_start.x << ", " << m_start.y << ")\n"
		 << "End point (" << m_end.x << ", " << m_end.y << ")\n";
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_start, m_end, GetOutlineColor());
}

