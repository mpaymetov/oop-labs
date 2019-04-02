#pragma once
#include "SolidShape.h"
#include "Point.h"

class CCircle final : public CSolidShape
{
public:
	CCircle(const CPoint& center, const double radius, const std::string& outlineColor, const std::string& fillColor);
	~CCircle() = default;
	
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(ICanvas & canvas) const override;
	
	CPoint GetCenter() const;
	double GetRadius() const;
	void SetCenter(CPoint point);
	void SetRadius(double radius);

private:
	CPoint m_center;
	double m_radius;
};
