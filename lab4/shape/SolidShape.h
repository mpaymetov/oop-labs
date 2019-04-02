#pragma once
#include "ISolidShape.h"

class CSolidShape : public virtual ISolidShape
{
public:
	CSolidShape(const std::string& outlineColor, const std::string& fillColor);

	std::string GetFillColor() const override final;
	void SetFillColor(std::string const& color);

private:
	std::string m_fillColor = "000000";

};