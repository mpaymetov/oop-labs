#pragma once
#include "SolidShape.h"
#include "Point.h"

class CRectangle final : public CSolidShape, public ICanvasDrawable
{
public:
	CRectangle(const CPoint& leftTop, const double& width, const double& height, const uint32_t& outlineColor, const uint32_t& fillColor);
	~CRectangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	void Draw(ICanvas & canvas) const override;

	CPoint GetLeftTop() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	CPoint m_leftTop;
	double m_width;
	double m_height;
};
