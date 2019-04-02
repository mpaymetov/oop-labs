#pragma once
#include "SolidShape.h"
#include "Point.h"

class CTriangle final : public CSolidShape
{
public:
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3,
		const std::string& outlineColor, const std::string& fillColor);
	~CTriangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(ICanvas & canvas) const override;

private:
	CPoint m_vertex1, m_vertex2, m_vertex3;
};
