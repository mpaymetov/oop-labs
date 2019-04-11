#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape() {}
	CShape(const uint32_t outlineColor);

	uint32_t GetOutlineColor() const override final;
	void SetOutlineColor(uint32_t const color);

	std::string ToString() const override;

private:
	uint32_t m_outlineColor = 0;

	virtual void AppendProperties(std::ostream& strm) const = 0;
};