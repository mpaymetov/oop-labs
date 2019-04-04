#pragma once
#include "Shape.h"

class ISolidShape : public virtual IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};
