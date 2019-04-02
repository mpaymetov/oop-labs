#pragma once
#include "Shape.h"
#include "Point.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment(const CPoint & first, const CPoint & second, const std::string& color);
	~CLineSegment() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(ICanvas & canvas) const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_start;
	CPoint m_end;
};

