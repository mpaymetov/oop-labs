#pragma once
#include "Shape.h"

class ISolidShape : public virtual CShape
{
public:
	virtual std::string GetFillColor() const = 0;
};
