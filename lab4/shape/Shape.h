#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape() {}
	CShape(const uint32_t outlineColor);

	uint32_t GetOutlineColor() const override final;
	void SetOutlineColor(uint32_t const color);

private:
	uint32_t m_outlineColor = 0;
};