#pragma once
#include "ISolidShape.h"

class CSolidShape : public virtual ISolidShape
{
public:
	CSolidShape(const uint32_t outlineColor, const uint32_t fillColor);

	uint32_t GetOutlineColor() const override final;
	void SetOutlineColor(uint32_t const color);

	uint32_t GetFillColor() const override final;
	void SetFillColor(uint32_t const color);

private:
	uint32_t m_fillColor = 0;
	uint32_t m_outlineColor = 0;
};