#include "stdafx.h"
#include "Circle.h"
#include "SolidShape.h"

CCircle::CCircle(const CPoint& center, const double radius, const uint32_t outlineColor, const uint32_t fillColor)
	: CSolidShape(outlineColor, fillColor)
	, m_center(center)
	, m_radius(radius)
{
}

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

std::string CCircle::GetType() const
{
	return "Circle";
}

void CCircle::AppendProperties(std::ostream& strm) const
{
	strm << std::fixed << std::setprecision(2);

	strm << "Center (" << m_center.x << ", " << m_center.y << ")\n"
		 << "Radius: " << GetRadius() << "\n";

	return;
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_center, m_radius, GetOutlineColor());
	canvas.FillCircle(m_center, m_radius, GetFillColor());
}

