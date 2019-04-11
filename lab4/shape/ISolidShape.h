#pragma once
#include "Shape.h"

class ISolidShape : public IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;
};
