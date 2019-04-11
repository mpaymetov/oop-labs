#pragma once
#include "Shape.h"
#include "Point.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment(const CPoint& first, const CPoint& second, const uint32_t color);
	~CLineSegment() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string GetType() const override;

	void Draw(ICanvas & canvas) const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_start;
	CPoint m_end;

	void AppendProperties(std::ostream& strm) const override;
};

