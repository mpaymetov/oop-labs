#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape() {};
	CShape(const std::string& outlineColor);

	std::string GetOutlineColor() const override final;
	void SetOutlineColor(std::string const& color);

private:
	std::string m_outlineColor;
};